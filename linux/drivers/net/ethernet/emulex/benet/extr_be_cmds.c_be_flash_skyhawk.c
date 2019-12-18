#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct image_hdr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_images; } ;
struct flash_section_info {TYPE_3__* fsec_entry; TYPE_2__ fsec_hdr; } ;
struct flash_file_hdr_g3 {int dummy; } ;
struct firmware {int size; int /*<<< orphan*/  const* data; } ;
struct device {int dummy; } ;
struct be_dma_mem {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_6__ {int optype; int /*<<< orphan*/  type; int /*<<< orphan*/  pad_size; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int EINVAL ; 
#define  MCC_ADDL_STATUS_INVALID_SIGNATURE 129 
#define  MCC_ADDL_STATUS_MISSING_SIGNATURE 128 
 scalar_t__ MCC_STATUS_FAILED ; 
 scalar_t__ MCC_STATUS_ILLEGAL_FIELD ; 
 scalar_t__ MCC_STATUS_ILLEGAL_REQUEST ; 
 int OPTYPE_OFFSET_SPECIFIED ; 
 int OPTYPE_UFI_DIR ; 
 int addl_status (int) ; 
 scalar_t__ base_status (int) ; 
 int be_check_flash_crc (struct be_adapter*,int /*<<< orphan*/  const*,int,int,int,int,int*) ; 
 int be_flash (struct be_adapter*,int /*<<< orphan*/  const*,struct be_dma_mem*,int,int,int) ; 
 int be_get_img_optype (TYPE_3__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct flash_section_info* get_fsec_info (struct be_adapter*,int,struct firmware const*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_flash_skyhawk(struct be_adapter *adapter,
			    const struct firmware *fw,
			    struct be_dma_mem *flash_cmd, int num_of_images)
{
	int img_hdrs_size = num_of_images * sizeof(struct image_hdr);
	bool crc_match, old_fw_img, flash_offset_support = true;
	struct device *dev = &adapter->pdev->dev;
	struct flash_section_info *fsec = NULL;
	u32 img_offset, img_size, img_type;
	u16 img_optype, flash_optype;
	int status, i, filehdr_size;
	const u8 *p;

	filehdr_size = sizeof(struct flash_file_hdr_g3);
	fsec = get_fsec_info(adapter, filehdr_size + img_hdrs_size, fw);
	if (!fsec) {
		dev_err(dev, "Invalid Cookie. FW image may be corrupted\n");
		return -EINVAL;
	}

retry_flash:
	for (i = 0; i < le32_to_cpu(fsec->fsec_hdr.num_images); i++) {
		img_offset = le32_to_cpu(fsec->fsec_entry[i].offset);
		img_size   = le32_to_cpu(fsec->fsec_entry[i].pad_size);
		img_type   = le32_to_cpu(fsec->fsec_entry[i].type);
		img_optype = be_get_img_optype(fsec->fsec_entry[i]);
		old_fw_img = fsec->fsec_entry[i].optype == 0xFFFF;

		if (img_optype == 0xFFFF)
			continue;

		if (flash_offset_support)
			flash_optype = OPTYPE_OFFSET_SPECIFIED;
		else
			flash_optype = img_optype;

		/* Don't bother verifying CRC if an old FW image is being
		 * flashed
		 */
		if (old_fw_img)
			goto flash;

		status = be_check_flash_crc(adapter, fw->data, img_offset,
					    img_size, filehdr_size +
					    img_hdrs_size, flash_optype,
					    &crc_match);
		if (base_status(status) == MCC_STATUS_ILLEGAL_REQUEST ||
		    base_status(status) == MCC_STATUS_ILLEGAL_FIELD) {
			/* The current FW image on the card does not support
			 * OFFSET based flashing. Retry using older mechanism
			 * of OPTYPE based flashing
			 */
			if (flash_optype == OPTYPE_OFFSET_SPECIFIED) {
				flash_offset_support = false;
				goto retry_flash;
			}

			/* The current FW image on the card does not recognize
			 * the new FLASH op_type. The FW download is partially
			 * complete. Reboot the server now to enable FW image
			 * to recognize the new FLASH op_type. To complete the
			 * remaining process, download the same FW again after
			 * the reboot.
			 */
			dev_err(dev, "Flash incomplete. Reset the server\n");
			dev_err(dev, "Download FW image again after reset\n");
			return -EAGAIN;
		} else if (status) {
			dev_err(dev, "Could not get CRC for 0x%x region\n",
				img_optype);
			return -EFAULT;
		}

		if (crc_match)
			continue;

flash:
		p = fw->data + filehdr_size + img_offset + img_hdrs_size;
		if (p + img_size > fw->data + fw->size)
			return -1;

		status = be_flash(adapter, p, flash_cmd, flash_optype, img_size,
				  img_offset);

		/* The current FW image on the card does not support OFFSET
		 * based flashing. Retry using older mechanism of OPTYPE based
		 * flashing
		 */
		if (base_status(status) == MCC_STATUS_ILLEGAL_FIELD &&
		    flash_optype == OPTYPE_OFFSET_SPECIFIED) {
			flash_offset_support = false;
			goto retry_flash;
		}

		/* For old FW images ignore ILLEGAL_FIELD error or errors on
		 * UFI_DIR region
		 */
		if (old_fw_img &&
		    (base_status(status) == MCC_STATUS_ILLEGAL_FIELD ||
		     (img_optype == OPTYPE_UFI_DIR &&
		      base_status(status) == MCC_STATUS_FAILED))) {
			continue;
		} else if (status) {
			dev_err(dev, "Flashing section type 0x%x failed\n",
				img_type);

			switch (addl_status(status)) {
			case MCC_ADDL_STATUS_MISSING_SIGNATURE:
				dev_err(dev,
					"Digital signature missing in FW\n");
				return -EINVAL;
			case MCC_ADDL_STATUS_INVALID_SIGNATURE:
				dev_err(dev,
					"Invalid digital signature in FW\n");
				return -EINVAL;
			default:
				return -EFAULT;
			}
		}
	}
	return 0;
}