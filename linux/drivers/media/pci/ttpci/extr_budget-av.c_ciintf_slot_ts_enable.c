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
struct budget_av {int /*<<< orphan*/  slot_status; TYPE_1__ budget; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUDGET_VIDEO_PORTA ; 
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttpci_budget_set_video_port (struct saa7146_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ciintf_slot_ts_enable(struct dvb_ca_en50221 *ca, int slot)
{
	struct budget_av *budget_av = (struct budget_av *) ca->data;
	struct saa7146_dev *saa = budget_av->budget.dev;

	if (slot != 0)
		return -EINVAL;

	dprintk(1, "ciintf_slot_ts_enable: %d\n", budget_av->slot_status);

	ttpci_budget_set_video_port(saa, BUDGET_VIDEO_PORTA);

	return 0;
}