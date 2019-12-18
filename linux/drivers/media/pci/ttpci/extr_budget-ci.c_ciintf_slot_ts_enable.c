#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct saa7146_dev {int dummy; } ;
struct dvb_ca_en50221 {scalar_t__ data; } ;
struct TYPE_3__ {struct saa7146_dev* dev; } ;
struct budget_ci {TYPE_1__ budget; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUDGET_VIDEO_PORTA ; 
 int CICONTROL_ENABLETS ; 
 int /*<<< orphan*/  DEBIADDR_CICONTROL ; 
 int /*<<< orphan*/  DEBICICTL ; 
 int EINVAL ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTLO ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int ttpci_budget_debiread (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttpci_budget_debiwrite (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttpci_budget_set_video_port (struct saa7146_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ciintf_slot_ts_enable(struct dvb_ca_en50221 *ca, int slot)
{
	struct budget_ci *budget_ci = (struct budget_ci *) ca->data;
	struct saa7146_dev *saa = budget_ci->budget.dev;
	int tmp;

	if (slot != 0)
		return -EINVAL;

	saa7146_setgpio(saa, 1, SAA7146_GPIO_OUTLO);

	tmp = ttpci_budget_debiread(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1, 1, 0);
	ttpci_budget_debiwrite(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1,
			       tmp | CICONTROL_ENABLETS, 1, 0);

	ttpci_budget_set_video_port(saa, BUDGET_VIDEO_PORTA);
	return 0;
}