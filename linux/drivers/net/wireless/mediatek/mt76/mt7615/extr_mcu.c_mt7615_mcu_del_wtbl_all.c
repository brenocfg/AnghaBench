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
struct wtbl_req_hdr {int /*<<< orphan*/  operation; } ;
struct mt7615_dev {int /*<<< orphan*/  mt76; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_EXT_CMD_WTBL_UPDATE ; 
 int /*<<< orphan*/  WTBL_RESET_ALL ; 
 int __mt76_mcu_send_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wtbl_req_hdr*,int,int) ; 

int mt7615_mcu_del_wtbl_all(struct mt7615_dev *dev)
{
	struct wtbl_req_hdr req = {
		.operation = WTBL_RESET_ALL,
	};

	return __mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_WTBL_UPDATE,
				   &req, sizeof(req), true);
}