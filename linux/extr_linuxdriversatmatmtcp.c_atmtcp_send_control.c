#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
struct atmtcp_control {int type; int /*<<< orphan*/  vcc; TYPE_1__ hdr; } ;
struct atm_vcc {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  (* push ) (struct atm_vcc*,struct sk_buff*) ;} ;
typedef  int /*<<< orphan*/  atm_kptr_t ;
struct TYPE_4__ {struct atm_vcc* vcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMTCP_HDR_MAGIC ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EUNATCH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* PRIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_force_charge (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  sk_sleep (int /*<<< orphan*/ ) ; 
 struct atmtcp_control* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 
 int test_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int atmtcp_send_control(struct atm_vcc *vcc,int type,
    const struct atmtcp_control *msg,int flag)
{
	DECLARE_WAITQUEUE(wait,current);
	struct atm_vcc *out_vcc;
	struct sk_buff *skb;
	struct atmtcp_control *new_msg;
	int old_test;
	int error = 0;

	out_vcc = PRIV(vcc->dev) ? PRIV(vcc->dev)->vcc : NULL;
	if (!out_vcc) return -EUNATCH;
	skb = alloc_skb(sizeof(*msg),GFP_KERNEL);
	if (!skb) return -ENOMEM;
	mb();
	out_vcc = PRIV(vcc->dev) ? PRIV(vcc->dev)->vcc : NULL;
	if (!out_vcc) {
		dev_kfree_skb(skb);
		return -EUNATCH;
	}
	atm_force_charge(out_vcc,skb->truesize);
	new_msg = skb_put(skb, sizeof(*new_msg));
	*new_msg = *msg;
	new_msg->hdr.length = ATMTCP_HDR_MAGIC;
	new_msg->type = type;
	memset(&new_msg->vcc,0,sizeof(atm_kptr_t));
	*(struct atm_vcc **) &new_msg->vcc = vcc;
	old_test = test_bit(flag,&vcc->flags);
	out_vcc->push(out_vcc,skb);
	add_wait_queue(sk_sleep(sk_atm(vcc)), &wait);
	while (test_bit(flag,&vcc->flags) == old_test) {
		mb();
		out_vcc = PRIV(vcc->dev) ? PRIV(vcc->dev)->vcc : NULL;
		if (!out_vcc) {
			error = -EUNATCH;
			break;
		}
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule();
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(sk_sleep(sk_atm(vcc)), &wait);
	return error;
}