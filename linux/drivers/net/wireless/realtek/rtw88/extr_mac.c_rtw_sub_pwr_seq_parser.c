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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtw_pwr_seq_cmd {int cmd; int intf_mask; int cut_mask; int mask; int value; int /*<<< orphan*/  offset; int /*<<< orphan*/  base; } ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RTW_PWR_ADDR_SDIO ; 
#define  RTW_PWR_CMD_DELAY 131 
 int RTW_PWR_CMD_END ; 
#define  RTW_PWR_CMD_POLLING 130 
#define  RTW_PWR_CMD_READ 129 
#define  RTW_PWR_CMD_WRITE 128 
 int RTW_PWR_DELAY_US ; 
 int /*<<< orphan*/  SDIO_LOCAL_OFFSET ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_pwr_cmd_polling (struct rtw_dev*,struct rtw_pwr_seq_cmd*) ; 
 int rtw_read8 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtw_sub_pwr_seq_parser(struct rtw_dev *rtwdev, u8 intf_mask,
				  u8 cut_mask, struct rtw_pwr_seq_cmd *cmd)
{
	struct rtw_pwr_seq_cmd *cur_cmd;
	u32 offset;
	u8 value;

	for (cur_cmd = cmd; cur_cmd->cmd != RTW_PWR_CMD_END; cur_cmd++) {
		if (!(cur_cmd->intf_mask & intf_mask) ||
		    !(cur_cmd->cut_mask & cut_mask))
			continue;

		switch (cur_cmd->cmd) {
		case RTW_PWR_CMD_WRITE:
			offset = cur_cmd->offset;

			if (cur_cmd->base == RTW_PWR_ADDR_SDIO)
				offset |= SDIO_LOCAL_OFFSET;

			value = rtw_read8(rtwdev, offset);
			value &= ~cur_cmd->mask;
			value |= (cur_cmd->value & cur_cmd->mask);
			rtw_write8(rtwdev, offset, value);
			break;
		case RTW_PWR_CMD_POLLING:
			if (rtw_pwr_cmd_polling(rtwdev, cur_cmd))
				return -EBUSY;
			break;
		case RTW_PWR_CMD_DELAY:
			if (cur_cmd->value == RTW_PWR_DELAY_US)
				udelay(cur_cmd->offset);
			else
				mdelay(cur_cmd->offset);
			break;
		case RTW_PWR_CMD_READ:
			break;
		default:
			return -EINVAL;
		}
	}

	return 0;
}