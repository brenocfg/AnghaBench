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
typedef  int /*<<< orphan*/  zero ;
typedef  int /*<<< orphan*/  u8 ;
struct anybuss_host {int softint_pending; int /*<<< orphan*/  wq; int /*<<< orphan*/  qlock; int /*<<< orphan*/  powerq; int /*<<< orphan*/  qcache; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  ind_ab; int /*<<< orphan*/  power_on; struct anybuss_client* client; } ;
struct anybuss_client {int /*<<< orphan*/  (* on_area_updated ) (struct anybuss_client*) ;int /*<<< orphan*/  (* on_online_changed ) (struct anybuss_client*,int) ;} ;
struct ab_task {int /*<<< orphan*/  (* done_fn ) (struct anybuss_host*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int EVENT_CAUSE_DC ; 
 unsigned int EVENT_CAUSE_FBOF ; 
 unsigned int EVENT_CAUSE_FBON ; 
 unsigned int IND_AX_EVNT ; 
 int /*<<< orphan*/  IND_AX_FBCTRL ; 
 int /*<<< orphan*/  REG_EVENT_CAUSE ; 
 int /*<<< orphan*/  REG_IND_AP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ab_task_enqueue (struct ab_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ab_task_put (struct ab_task*) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 struct ab_task* create_area_writer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  softint_ack (struct anybuss_host*) ; 
 int /*<<< orphan*/  stub1 (struct anybuss_client*,int) ; 
 int /*<<< orphan*/  stub2 (struct anybuss_client*,int) ; 
 int /*<<< orphan*/  stub3 (struct anybuss_client*) ; 

__attribute__((used)) static void process_softint(struct anybuss_host *cd)
{
	struct anybuss_client *client = cd->client;
	static const u8 zero;
	int ret;
	unsigned int ind_ap, ev;
	struct ab_task *t;

	if (!cd->power_on)
		return;
	if (cd->softint_pending)
		return;
	regmap_read(cd->regmap, REG_IND_AP, &ind_ap);
	if (!((atomic_read(&cd->ind_ab) ^ ind_ap) & IND_AX_EVNT))
		return;
	/* process software interrupt */
	regmap_read(cd->regmap, REG_EVENT_CAUSE, &ev);
	if (ev & EVENT_CAUSE_FBON) {
		if (client->on_online_changed)
			client->on_online_changed(client, true);
		dev_dbg(cd->dev, "Fieldbus ON");
	}
	if (ev & EVENT_CAUSE_FBOF) {
		if (client->on_online_changed)
			client->on_online_changed(client, false);
		dev_dbg(cd->dev, "Fieldbus OFF");
	}
	if (ev & EVENT_CAUSE_DC) {
		if (client->on_area_updated)
			client->on_area_updated(client);
		dev_dbg(cd->dev, "Fieldbus data changed");
	}
	/*
	 * reset the event cause bits.
	 * this must be done while owning the fbctrl area, so we'll
	 * enqueue a task to do that.
	 */
	t = create_area_writer(cd->qcache, IND_AX_FBCTRL,
			       REG_EVENT_CAUSE, &zero, sizeof(zero));
	if (!t) {
		ret = -ENOMEM;
		goto out;
	}
	t->done_fn = softint_ack;
	ret = ab_task_enqueue(t, cd->powerq, &cd->qlock, &cd->wq);
	ab_task_put(t);
	cd->softint_pending = true;
out:
	WARN_ON(ret);
	if (ret)
		softint_ack(cd);
}