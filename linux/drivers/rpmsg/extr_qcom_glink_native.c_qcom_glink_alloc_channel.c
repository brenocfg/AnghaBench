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
struct qcom_glink {int dummy; } ;
struct glink_channel {int /*<<< orphan*/  refcount; int /*<<< orphan*/  riids; int /*<<< orphan*/  liids; int /*<<< orphan*/  intent_work; int /*<<< orphan*/  done_intents; int /*<<< orphan*/  intent_req_comp; int /*<<< orphan*/  open_ack; int /*<<< orphan*/  open_req; int /*<<< orphan*/  name; struct qcom_glink* glink; int /*<<< orphan*/  intent_req_lock; int /*<<< orphan*/  intent_lock; int /*<<< orphan*/  recv_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct glink_channel* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct glink_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_glink_rx_done_work ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct glink_channel *qcom_glink_alloc_channel(struct qcom_glink *glink,
						      const char *name)
{
	struct glink_channel *channel;

	channel = kzalloc(sizeof(*channel), GFP_KERNEL);
	if (!channel)
		return ERR_PTR(-ENOMEM);

	/* Setup glink internal glink_channel data */
	spin_lock_init(&channel->recv_lock);
	spin_lock_init(&channel->intent_lock);
	mutex_init(&channel->intent_req_lock);

	channel->glink = glink;
	channel->name = kstrdup(name, GFP_KERNEL);

	init_completion(&channel->open_req);
	init_completion(&channel->open_ack);
	init_completion(&channel->intent_req_comp);

	INIT_LIST_HEAD(&channel->done_intents);
	INIT_WORK(&channel->intent_work, qcom_glink_rx_done_work);

	idr_init(&channel->liids);
	idr_init(&channel->riids);
	kref_init(&channel->refcount);

	return channel;
}