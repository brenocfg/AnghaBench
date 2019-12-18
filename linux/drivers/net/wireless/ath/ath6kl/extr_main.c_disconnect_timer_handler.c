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
struct timer_list {int dummy; } ;
struct ath6kl_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_disconnect (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_init_profile_info (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  disconnect_timer ; 
 struct ath6kl_vif* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ath6kl_vif* vif ; 

void disconnect_timer_handler(struct timer_list *t)
{
	struct ath6kl_vif *vif = from_timer(vif, t, disconnect_timer);

	ath6kl_init_profile_info(vif);
	ath6kl_disconnect(vif);
}