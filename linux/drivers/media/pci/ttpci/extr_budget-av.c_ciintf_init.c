#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct saa7146_dev {int dummy; } ;
struct dvb_ca_en50221 {int dummy; } ;
struct TYPE_5__ {struct budget_av* data; int /*<<< orphan*/  poll_slot_status; int /*<<< orphan*/  slot_ts_enable; int /*<<< orphan*/  slot_shutdown; int /*<<< orphan*/  slot_reset; int /*<<< orphan*/  write_cam_control; int /*<<< orphan*/  read_cam_control; int /*<<< orphan*/  write_attribute_mem; int /*<<< orphan*/  read_attribute_mem; int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {int ci_present; int /*<<< orphan*/  dvb_adapter; struct saa7146_dev* dev; } ;
struct budget_av {TYPE_2__ ca; TYPE_1__ budget; int /*<<< orphan*/  slot_status; } ;

/* Variables and functions */
 int MASK_11 ; 
 int MASK_27 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTLO ; 
 int /*<<< orphan*/  SLOTSTATUS_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ciintf_poll_slot_status ; 
 int /*<<< orphan*/  ciintf_read_attribute_mem ; 
 int /*<<< orphan*/  ciintf_read_cam_control ; 
 int /*<<< orphan*/  ciintf_slot_reset ; 
 int /*<<< orphan*/  ciintf_slot_shutdown ; 
 int /*<<< orphan*/  ciintf_slot_ts_enable ; 
 int /*<<< orphan*/  ciintf_write_attribute_mem ; 
 int /*<<< orphan*/  ciintf_write_cam_control ; 
 int dvb_ca_en50221_init (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ciintf_init(struct budget_av *budget_av)
{
	struct saa7146_dev *saa = budget_av->budget.dev;
	int result;

	memset(&budget_av->ca, 0, sizeof(struct dvb_ca_en50221));

	saa7146_setgpio(saa, 0, SAA7146_GPIO_OUTLO);
	saa7146_setgpio(saa, 1, SAA7146_GPIO_OUTLO);
	saa7146_setgpio(saa, 2, SAA7146_GPIO_OUTLO);
	saa7146_setgpio(saa, 3, SAA7146_GPIO_OUTLO);

	/* Enable DEBI pins */
	saa7146_write(saa, MC1, MASK_27 | MASK_11);

	/* register CI interface */
	budget_av->ca.owner = THIS_MODULE;
	budget_av->ca.read_attribute_mem = ciintf_read_attribute_mem;
	budget_av->ca.write_attribute_mem = ciintf_write_attribute_mem;
	budget_av->ca.read_cam_control = ciintf_read_cam_control;
	budget_av->ca.write_cam_control = ciintf_write_cam_control;
	budget_av->ca.slot_reset = ciintf_slot_reset;
	budget_av->ca.slot_shutdown = ciintf_slot_shutdown;
	budget_av->ca.slot_ts_enable = ciintf_slot_ts_enable;
	budget_av->ca.poll_slot_status = ciintf_poll_slot_status;
	budget_av->ca.data = budget_av;
	budget_av->budget.ci_present = 1;
	budget_av->slot_status = SLOTSTATUS_NONE;

	if ((result = dvb_ca_en50221_init(&budget_av->budget.dvb_adapter,
					  &budget_av->ca, 0, 1)) != 0) {
		pr_err("ci initialisation failed\n");
		goto error;
	}

	pr_info("ci interface initialised\n");
	return 0;

error:
	saa7146_write(saa, MC1, MASK_27);
	return result;
}