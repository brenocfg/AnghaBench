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
struct wilc_vif {int dummy; } ;
struct timer_list {int dummy; } ;
struct host_if_msg {int dummy; } ;
struct host_if_drv {struct wilc_vif* connect_timer_vif; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct host_if_msg*) ; 
 int /*<<< orphan*/  connect_timer ; 
 struct host_if_drv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_connect_timeout ; 
 struct host_if_drv* hif_drv ; 
 int /*<<< orphan*/  kfree (struct host_if_msg*) ; 
 struct host_if_msg* wilc_alloc_work (struct wilc_vif*,int /*<<< orphan*/ ,int) ; 
 int wilc_enqueue_work (struct host_if_msg*) ; 

__attribute__((used)) static void timer_connect_cb(struct timer_list *t)
{
	struct host_if_drv *hif_drv = from_timer(hif_drv, t,
						      connect_timer);
	struct wilc_vif *vif = hif_drv->connect_timer_vif;
	struct host_if_msg *msg;
	int result;

	msg = wilc_alloc_work(vif, handle_connect_timeout, false);
	if (IS_ERR(msg))
		return;

	result = wilc_enqueue_work(msg);
	if (result)
		kfree(msg);
}