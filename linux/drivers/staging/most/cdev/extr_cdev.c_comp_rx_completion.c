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
struct mbo {int /*<<< orphan*/  hdm_channel_id; int /*<<< orphan*/  ifp; } ;
struct comp_channel {int /*<<< orphan*/  wq; int /*<<< orphan*/  fifo; int /*<<< orphan*/  unlink; int /*<<< orphan*/  dev; int /*<<< orphan*/  access_ref; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 struct comp_channel* get_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,struct mbo**,int) ; 
 scalar_t__ kfifo_is_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int comp_rx_completion(struct mbo *mbo)
{
	struct comp_channel *c;

	if (!mbo)
		return -EINVAL;

	c = get_channel(mbo->ifp, mbo->hdm_channel_id);
	if (!c)
		return -ENXIO;

	spin_lock(&c->unlink);
	if (!c->access_ref || !c->dev) {
		spin_unlock(&c->unlink);
		return -ENODEV;
	}
	kfifo_in(&c->fifo, &mbo, 1);
	spin_unlock(&c->unlink);
#ifdef DEBUG_MESG
	if (kfifo_is_full(&c->fifo))
		pr_info("WARN: Fifo is full\n");
#endif
	wake_up_interruptible(&c->wq);
	return 0;
}