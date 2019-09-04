#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct edmacc_param {scalar_t__ a_b_cnt; scalar_t__ ccnt; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__ chan; } ;
struct edma_chan {int missed; TYPE_3__ vchan; int /*<<< orphan*/ * slot; int /*<<< orphan*/  edesc; struct edma_cc* ecc; } ;
struct edma_cc {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  edma_clean_channel (struct edma_chan*) ; 
 int edma_read_slot (struct edma_cc*,int /*<<< orphan*/ ,struct edmacc_param*) ; 
 int /*<<< orphan*/  edma_start (struct edma_chan*) ; 
 int /*<<< orphan*/  edma_stop (struct edma_chan*) ; 
 int /*<<< orphan*/  edma_trigger_channel (struct edma_chan*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void edma_error_handler(struct edma_chan *echan)
{
	struct edma_cc *ecc = echan->ecc;
	struct device *dev = echan->vchan.chan.device->dev;
	struct edmacc_param p;
	int err;

	if (!echan->edesc)
		return;

	spin_lock(&echan->vchan.lock);

	err = edma_read_slot(ecc, echan->slot[0], &p);

	/*
	 * Issue later based on missed flag which will be sure
	 * to happen as:
	 * (1) we finished transmitting an intermediate slot and
	 *     edma_execute is coming up.
	 * (2) or we finished current transfer and issue will
	 *     call edma_execute.
	 *
	 * Important note: issuing can be dangerous here and
	 * lead to some nasty recursion when we are in a NULL
	 * slot. So we avoid doing so and set the missed flag.
	 */
	if (err || (p.a_b_cnt == 0 && p.ccnt == 0)) {
		dev_dbg(dev, "Error on null slot, setting miss\n");
		echan->missed = 1;
	} else {
		/*
		 * The slot is already programmed but the event got
		 * missed, so its safe to issue it here.
		 */
		dev_dbg(dev, "Missed event, TRIGGERING\n");
		edma_clean_channel(echan);
		edma_stop(echan);
		edma_start(echan);
		edma_trigger_channel(echan);
	}
	spin_unlock(&echan->vchan.lock);
}