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
struct ilo_hwinfo {TYPE_1__* ilo_dev; } ;
struct ccb {int dummy; } ;
struct ccb_data {struct ccb driver_ccb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int MAX_WAIT ; 
 int /*<<< orphan*/  SENDQ ; 
 int /*<<< orphan*/  WAIT_TIME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  doorbell_set (struct ccb*) ; 
 scalar_t__ ilo_pkt_dequeue (struct ilo_hwinfo*,struct ccb*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ilo_pkt_enqueue (struct ilo_hwinfo*,struct ccb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ilo_ccb_verify(struct ilo_hwinfo *hw, struct ccb_data *data)
{
	int pkt_id, i;
	struct ccb *driver_ccb = &data->driver_ccb;

	/* make sure iLO is really handling requests */
	for (i = MAX_WAIT; i > 0; i--) {
		if (ilo_pkt_dequeue(hw, driver_ccb, SENDQ, &pkt_id, NULL, NULL))
			break;
		udelay(WAIT_TIME);
	}

	if (i == 0) {
		dev_err(&hw->ilo_dev->dev, "Open could not dequeue a packet\n");
		return -EBUSY;
	}

	ilo_pkt_enqueue(hw, driver_ccb, SENDQ, pkt_id, 0);
	doorbell_set(driver_ccb);
	return 0;
}