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
struct sd_info {scalar_t__ sd_addr; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESELECT_CARD ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R0 ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int /*<<< orphan*/  SELECT_CARD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sd_select_card(struct rtsx_chip *chip, int select)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;
	u8 cmd_idx, cmd_type;
	u32 addr;

	if (select) {
		cmd_idx = SELECT_CARD;
		cmd_type = SD_RSP_TYPE_R1;
		addr = sd_card->sd_addr;
	} else {
		cmd_idx = DESELECT_CARD;
		cmd_type = SD_RSP_TYPE_R0;
		addr = 0;
	}

	retval = sd_send_cmd_get_rsp(chip, cmd_idx, addr, cmd_type, NULL, 0);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}