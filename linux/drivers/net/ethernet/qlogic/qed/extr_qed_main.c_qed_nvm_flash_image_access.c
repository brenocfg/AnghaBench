#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct qed_nvm_image_att {int start_addr; int length; } ;
struct TYPE_4__ {int num_images; TYPE_1__* image_att; } ;
struct qed_hwfn {TYPE_2__ nvm_info; } ;
struct qed_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {scalar_t__ image_type; int nvm_start_addr; int len; } ;

/* Variables and functions */
 scalar_t__ const BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_ERR (struct qed_dev*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,scalar_t__ const,scalar_t__,scalar_t__,scalar_t__,...) ; 
 int ENOENT ; 
 int /*<<< orphan*/  NETIF_MSG_DRV ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_NVM_WRITE_NVRAM ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int qed_mcp_nvm_read (struct qed_dev*,scalar_t__,scalar_t__*,int) ; 
 int qed_mcp_nvm_write (struct qed_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 int qed_nvm_flash_image_access_crc (struct qed_dev*,struct qed_nvm_image_att*,scalar_t__*) ; 

__attribute__((used)) static int qed_nvm_flash_image_access(struct qed_dev *cdev, const u8 **data,
				      bool *check_resp)
{
	struct qed_nvm_image_att nvm_image;
	struct qed_hwfn *p_hwfn;
	bool is_crc = false;
	u32 image_type;
	int rc = 0, i;
	u16 len;

	*data += 4;
	image_type = **data;
	p_hwfn = QED_LEADING_HWFN(cdev);
	for (i = 0; i < p_hwfn->nvm_info.num_images; i++)
		if (image_type == p_hwfn->nvm_info.image_att[i].image_type)
			break;
	if (i == p_hwfn->nvm_info.num_images) {
		DP_ERR(cdev, "Failed to find nvram image of type %08x\n",
		       image_type);
		return -ENOENT;
	}

	nvm_image.start_addr = p_hwfn->nvm_info.image_att[i].nvm_start_addr;
	nvm_image.length = p_hwfn->nvm_info.image_att[i].len;

	DP_VERBOSE(cdev, NETIF_MSG_DRV,
		   "Read image %02x; type = %08x; NVM [%08x,...,%08x]\n",
		   **data, image_type, nvm_image.start_addr,
		   nvm_image.start_addr + nvm_image.length - 1);
	(*data)++;
	is_crc = !!(**data & BIT(0));
	(*data)++;
	len = *((u16 *)*data);
	*data += 2;
	if (is_crc) {
		u32 crc = 0;

		rc = qed_nvm_flash_image_access_crc(cdev, &nvm_image, &crc);
		if (rc) {
			DP_ERR(cdev, "Failed calculating CRC, rc = %d\n", rc);
			goto exit;
		}

		rc = qed_mcp_nvm_write(cdev, QED_NVM_WRITE_NVRAM,
				       (nvm_image.start_addr +
					nvm_image.length - 4), (u8 *)&crc, 4);
		if (rc)
			DP_ERR(cdev, "Failed writing to %08x, rc = %d\n",
			       nvm_image.start_addr + nvm_image.length - 4, rc);
		goto exit;
	}

	/* Iterate over the values for setting */
	while (len) {
		u32 offset, mask, value, cur_value;
		u8 buf[4];

		value = *((u32 *)*data);
		*data += 4;
		mask = *((u32 *)*data);
		*data += 4;
		offset = *((u32 *)*data);
		*data += 4;

		rc = qed_mcp_nvm_read(cdev, nvm_image.start_addr + offset, buf,
				      4);
		if (rc) {
			DP_ERR(cdev, "Failed reading from %08x\n",
			       nvm_image.start_addr + offset);
			goto exit;
		}

		cur_value = le32_to_cpu(*((__le32 *)buf));
		DP_VERBOSE(cdev, NETIF_MSG_DRV,
			   "NVM %08x: %08x -> %08x [Value %08x Mask %08x]\n",
			   nvm_image.start_addr + offset, cur_value,
			   (cur_value & ~mask) | (value & mask), value, mask);
		value = (value & mask) | (cur_value & ~mask);
		rc = qed_mcp_nvm_write(cdev, QED_NVM_WRITE_NVRAM,
				       nvm_image.start_addr + offset,
				       (u8 *)&value, 4);
		if (rc) {
			DP_ERR(cdev, "Failed writing to %08x\n",
			       nvm_image.start_addr + offset);
			goto exit;
		}

		len--;
	}
exit:
	return rc;
}