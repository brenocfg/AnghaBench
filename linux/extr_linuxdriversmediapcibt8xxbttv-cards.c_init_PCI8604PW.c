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
struct TYPE_3__ {TYPE_2__* pci; } ;
struct bttv {TYPE_1__ c; } ;
struct TYPE_4__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_GPIO_DATA ; 
 int /*<<< orphan*/  BT848_GPIO_OUT_EN ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int btread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static void
init_PCI8604PW(struct bttv *btv)
{
	int state;

	if ((PCI_SLOT(btv->c.pci->devfn) & ~3) != 0xC) {
		pr_warn("This is not a PCI-8604PW\n");
		return;
	}

	if (PCI_SLOT(btv->c.pci->devfn) != 0xD)
		return;

	btwrite(0x080002, BT848_GPIO_OUT_EN);

	state = (btread(BT848_GPIO_DATA) >> 21) & 7;

	for (;;) {
		switch (state) {
		case 1:
		case 5:
		case 6:
		case 4:
			pr_debug("PCI-8604PW in state %i, toggling pin\n",
				 state);
			btwrite(0x080000, BT848_GPIO_DATA);
			msleep(1);
			btwrite(0x000000, BT848_GPIO_DATA);
			msleep(1);
			break;
		case 7:
			pr_info("PCI-8604PW unlocked\n");
			return;
		case 0:
			/* FIXME: If we are in state 7 and toggle GPIO[19] one
			   more time, the CPLD goes into state 0, where PCI bus
			   mastering is inhibited again. We have not managed to
			   get out of that state. */

			pr_err("PCI-8604PW locked until reset\n");
			return;
		default:
			pr_err("PCI-8604PW in unknown state %i\n", state);
			return;
		}

		state = (state << 4) | ((btread(BT848_GPIO_DATA) >> 21) & 7);

		switch (state) {
		case 0x15:
		case 0x56:
		case 0x64:
		case 0x47:
		/* The transition from state 7 to state 0 is, as explained
		   above, valid but undesired and with this code impossible
		   as we exit as soon as we are in state 7.
		case 0x70: */
			break;
		default:
			pr_err("PCI-8604PW invalid transition %i -> %i\n",
			       state >> 4, state & 7);
			return;
		}
		state &= 7;
	}
}