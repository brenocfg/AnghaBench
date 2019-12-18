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
struct nfp_fl_lag {int /*<<< orphan*/  retrans_skbs; int /*<<< orphan*/  ida_handle; int /*<<< orphan*/  lock; int /*<<< orphan*/  group_list; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_fl_increment_version (struct nfp_fl_lag*) ; 
 int /*<<< orphan*/  nfp_fl_lag_do_work ; 

void nfp_flower_lag_init(struct nfp_fl_lag *lag)
{
	INIT_DELAYED_WORK(&lag->work, nfp_fl_lag_do_work);
	INIT_LIST_HEAD(&lag->group_list);
	mutex_init(&lag->lock);
	ida_init(&lag->ida_handle);

	__skb_queue_head_init(&lag->retrans_skbs);

	/* 0 is a reserved batch version so increment to first valid value. */
	nfp_fl_increment_version(lag);
}