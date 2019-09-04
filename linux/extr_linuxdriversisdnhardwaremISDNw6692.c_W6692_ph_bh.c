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
struct w6692_hw {int state; int /*<<< orphan*/  name; } ;
struct dchannel {int state; int /*<<< orphan*/  l1; struct w6692_hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANYSIGNAL ; 
 int /*<<< orphan*/  HW_DEACT_CNF ; 
 int /*<<< orphan*/  HW_DEACT_IND ; 
 int /*<<< orphan*/  HW_POWERUP_IND ; 
 int /*<<< orphan*/  HW_RESET_IND ; 
 int /*<<< orphan*/  INFO2 ; 
 int /*<<< orphan*/  INFO4_P10 ; 
 int /*<<< orphan*/  INFO4_P8 ; 
 int /*<<< orphan*/  LOSTFRAMING ; 
#define  W_L1CMD_RST 135 
#define  W_L1IND_AI10 134 
#define  W_L1IND_AI8 133 
#define  W_L1IND_ARD 132 
#define  W_L1IND_CD 131 
#define  W_L1IND_CE 130 
#define  W_L1IND_DRD 129 
#define  W_L1IND_LD 128 
 int /*<<< orphan*/  l1_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static void
W6692_ph_bh(struct dchannel *dch)
{
	struct w6692_hw *card = dch->hw;

	switch (card->state) {
	case W_L1CMD_RST:
		dch->state = 0;
		l1_event(dch->l1, HW_RESET_IND);
		break;
	case W_L1IND_CD:
		dch->state = 3;
		l1_event(dch->l1, HW_DEACT_CNF);
		break;
	case W_L1IND_DRD:
		dch->state = 3;
		l1_event(dch->l1, HW_DEACT_IND);
		break;
	case W_L1IND_CE:
		dch->state = 4;
		l1_event(dch->l1, HW_POWERUP_IND);
		break;
	case W_L1IND_LD:
		if (dch->state <= 5) {
			dch->state = 5;
			l1_event(dch->l1, ANYSIGNAL);
		} else {
			dch->state = 8;
			l1_event(dch->l1, LOSTFRAMING);
		}
		break;
	case W_L1IND_ARD:
		dch->state = 6;
		l1_event(dch->l1, INFO2);
		break;
	case W_L1IND_AI8:
		dch->state = 7;
		l1_event(dch->l1, INFO4_P8);
		break;
	case W_L1IND_AI10:
		dch->state = 7;
		l1_event(dch->l1, INFO4_P10);
		break;
	default:
		pr_debug("%s: TE unknown state %02x dch state %02x\n",
			 card->name, card->state, dch->state);
		break;
	}
	pr_debug("%s: TE newstate %02x\n", card->name, dch->state);
}