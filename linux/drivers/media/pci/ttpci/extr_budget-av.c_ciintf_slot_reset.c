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
struct TYPE_2__ {int /*<<< orphan*/  dvb_frontend; struct saa7146_dev* dev; } ;
struct budget_av {TYPE_1__ budget; scalar_t__ reinitialise_demod; int /*<<< orphan*/  slot_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUDGET_VIDEO_PORTB ; 
 int EINVAL ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTHI ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTLO ; 
 int /*<<< orphan*/  SLOTSTATUS_RESET ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  dvb_frontend_reinitialise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttpci_budget_set_video_port (struct saa7146_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ciintf_slot_reset(struct dvb_ca_en50221 *ca, int slot)
{
	struct budget_av *budget_av = (struct budget_av *) ca->data;
	struct saa7146_dev *saa = budget_av->budget.dev;

	if (slot != 0)
		return -EINVAL;

	dprintk(1, "ciintf_slot_reset\n");
	budget_av->slot_status = SLOTSTATUS_RESET;

	saa7146_setgpio(saa, 2, SAA7146_GPIO_OUTHI); /* disable card */

	saa7146_setgpio(saa, 0, SAA7146_GPIO_OUTHI); /* Vcc off */
	msleep(2);
	saa7146_setgpio(saa, 0, SAA7146_GPIO_OUTLO); /* Vcc on */
	msleep(20); /* 20 ms Vcc settling time */

	saa7146_setgpio(saa, 2, SAA7146_GPIO_OUTLO); /* enable card */
	ttpci_budget_set_video_port(saa, BUDGET_VIDEO_PORTB);
	msleep(20);

	/* reinitialise the frontend if necessary */
	if (budget_av->reinitialise_demod)
		dvb_frontend_reinitialise(budget_av->budget.dvb_frontend);

	return 0;
}