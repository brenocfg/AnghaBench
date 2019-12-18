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
struct sk_buff {int dummy; } ;
struct ath10k {int /*<<< orphan*/  svc_rdy_work; int /*<<< orphan*/  workqueue_aux; struct sk_buff* svc_rdy_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath10k_wmi_event_service_ready(struct ath10k *ar, struct sk_buff *skb)
{
	ar->svc_rdy_skb = skb;
	queue_work(ar->workqueue_aux, &ar->svc_rdy_work);
}