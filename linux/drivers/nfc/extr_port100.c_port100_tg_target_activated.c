#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct port100 {int cmd_type; TYPE_1__* interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  PORT100_CMD_TYPE_0 129 
#define  PORT100_CMD_TYPE_1 128 
 int PORT100_MDAA_TGT_HAS_BEEN_ACTIVATED_MASK ; 
 int PORT100_MDAA_TGT_WAS_ACTIVATED_MASK ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bool port100_tg_target_activated(struct port100 *dev, u8 tgt_activated)
{
	u8 mask;

	switch (dev->cmd_type) {
	case PORT100_CMD_TYPE_0:
		mask = PORT100_MDAA_TGT_HAS_BEEN_ACTIVATED_MASK;
		break;
	case PORT100_CMD_TYPE_1:
		mask = PORT100_MDAA_TGT_HAS_BEEN_ACTIVATED_MASK |
		       PORT100_MDAA_TGT_WAS_ACTIVATED_MASK;
		break;
	default:
		nfc_err(&dev->interface->dev, "Unknown command type\n");
		return false;
	}

	return ((tgt_activated & mask) == mask);
}