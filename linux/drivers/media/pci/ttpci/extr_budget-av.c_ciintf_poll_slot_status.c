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
struct saa7146_dev {int dummy; } ;
struct dvb_ca_en50221 {scalar_t__ data; } ;
struct TYPE_2__ {struct saa7146_dev* dev; } ;
struct budget_av {int slot_status; TYPE_1__ budget; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBICICAM ; 
 int DVB_CA_EN50221_POLL_CAM_PRESENT ; 
 int DVB_CA_EN50221_POLL_CAM_READY ; 
 int EINVAL ; 
 int MASK_06 ; 
 int /*<<< orphan*/  PSR ; 
 int /*<<< orphan*/  SAA7146_GPIO_INPUT ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTLO ; 
 int SLOTSTATUS_NONE ; 
 void* SLOTSTATUS_PRESENT ; 
 int SLOTSTATUS_READY ; 
 int SLOTSTATUS_RESET ; 
 int ciintf_read_attribute_mem (struct dvb_ca_en50221*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ciintf_slot_shutdown (struct dvb_ca_en50221*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int ttpci_budget_debiread (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ciintf_poll_slot_status(struct dvb_ca_en50221 *ca, int slot, int open)
{
	struct budget_av *budget_av = (struct budget_av *) ca->data;
	struct saa7146_dev *saa = budget_av->budget.dev;
	int result;

	if (slot != 0)
		return -EINVAL;

	/* test the card detect line - needs to be done carefully
	 * since it never goes high for some CAMs on this interface (e.g. topuptv) */
	if (budget_av->slot_status == SLOTSTATUS_NONE) {
		saa7146_setgpio(saa, 3, SAA7146_GPIO_INPUT);
		udelay(1);
		if (saa7146_read(saa, PSR) & MASK_06) {
			if (budget_av->slot_status == SLOTSTATUS_NONE) {
				budget_av->slot_status = SLOTSTATUS_PRESENT;
				pr_info("cam inserted A\n");
			}
		}
		saa7146_setgpio(saa, 3, SAA7146_GPIO_OUTLO);
	}

	/* We also try and read from IO memory to work round the above detection bug. If
	 * there is no CAM, we will get a timeout. Only done if there is no cam
	 * present, since this test actually breaks some cams :(
	 *
	 * if the CI interface is not open, we also do the above test since we
	 * don't care if the cam has problems - we'll be resetting it on open() anyway */
	if ((budget_av->slot_status == SLOTSTATUS_NONE) || (!open)) {
		saa7146_setgpio(budget_av->budget.dev, 1, SAA7146_GPIO_OUTLO);
		result = ttpci_budget_debiread(&budget_av->budget, DEBICICAM, 0, 1, 0, 1);
		if ((result >= 0) && (budget_av->slot_status == SLOTSTATUS_NONE)) {
			budget_av->slot_status = SLOTSTATUS_PRESENT;
			pr_info("cam inserted B\n");
		} else if (result < 0) {
			if (budget_av->slot_status != SLOTSTATUS_NONE) {
				ciintf_slot_shutdown(ca, slot);
				pr_info("cam ejected 5\n");
				return 0;
			}
		}
	}

	/* read from attribute memory in reset/ready state to know when the CAM is ready */
	if (budget_av->slot_status == SLOTSTATUS_RESET) {
		result = ciintf_read_attribute_mem(ca, slot, 0);
		if (result == 0x1d) {
			budget_av->slot_status = SLOTSTATUS_READY;
		}
	}

	/* work out correct return code */
	if (budget_av->slot_status != SLOTSTATUS_NONE) {
		if (budget_av->slot_status & SLOTSTATUS_READY) {
			return DVB_CA_EN50221_POLL_CAM_PRESENT | DVB_CA_EN50221_POLL_CAM_READY;
		}
		return DVB_CA_EN50221_POLL_CAM_PRESENT;
	}
	return 0;
}