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
typedef  int u32 ;
struct slot {int /*<<< orphan*/  hp_slot; struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
#define  ATN_LED_STATE_BLINK 130 
 int ATN_LED_STATE_MASK ; 
#define  ATN_LED_STATE_OFF 129 
#define  ATN_LED_STATE_ON 128 
 int ATN_LED_STATE_SHIFT ; 
 int /*<<< orphan*/  SLOT_REG (int /*<<< orphan*/ ) ; 
 int shpc_readl (struct controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpc_get_attention_status(struct slot *slot, u8 *status)
{
	struct controller *ctrl = slot->ctrl;
	u32 slot_reg = shpc_readl(ctrl, SLOT_REG(slot->hp_slot));
	u8 state = (slot_reg & ATN_LED_STATE_MASK) >> ATN_LED_STATE_SHIFT;

	switch (state) {
	case ATN_LED_STATE_ON:
		*status = 1;	/* On */
		break;
	case ATN_LED_STATE_BLINK:
		*status = 2;	/* Blink */
		break;
	case ATN_LED_STATE_OFF:
		*status = 0;	/* Off */
		break;
	default:
		*status = 0xFF;	/* Reserved */
		break;
	}

	return 0;
}