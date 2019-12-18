#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct ims_pcu_flash_fmt {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct ims_pcu {int /*<<< orphan*/  dev; int /*<<< orphan*/ * cmd_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IMS_PCU_BL_DATA_OFFSET ; 
 int /*<<< orphan*/  IMS_PCU_CMD_RESPONSE_TIMEOUT ; 
 int /*<<< orphan*/  READ_APP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 
 scalar_t__ get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int ims_pcu_execute_bl_command (struct ims_pcu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ims_pcu_verify_block(struct ims_pcu *pcu,
				u32 addr, u8 len, const u8 *data)
{
	struct ims_pcu_flash_fmt *fragment;
	int error;

	fragment = (void *)&pcu->cmd_buf[1];
	put_unaligned_le32(addr, &fragment->addr);
	fragment->len = len;

	error = ims_pcu_execute_bl_command(pcu, READ_APP, NULL, 5,
					IMS_PCU_CMD_RESPONSE_TIMEOUT);
	if (error) {
		dev_err(pcu->dev,
			"Failed to retrieve block at 0x%08x, len %d, error: %d\n",
			addr, len, error);
		return error;
	}

	fragment = (void *)&pcu->cmd_buf[IMS_PCU_BL_DATA_OFFSET];
	if (get_unaligned_le32(&fragment->addr) != addr ||
	    fragment->len != len) {
		dev_err(pcu->dev,
			"Wrong block when retrieving 0x%08x (0x%08x), len %d (%d)\n",
			addr, get_unaligned_le32(&fragment->addr),
			len, fragment->len);
		return -EINVAL;
	}

	if (memcmp(fragment->data, data, len)) {
		dev_err(pcu->dev,
			"Mismatch in block at 0x%08x, len %d\n",
			addr, len);
		return -EINVAL;
	}

	return 0;
}