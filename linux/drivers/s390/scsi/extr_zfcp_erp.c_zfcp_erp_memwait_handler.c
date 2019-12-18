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
struct zfcp_erp_action {int dummy; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct zfcp_erp_action* act ; 
 struct zfcp_erp_action* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  zfcp_erp_notify (struct zfcp_erp_action*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_erp_memwait_handler(struct timer_list *t)
{
	struct zfcp_erp_action *act = from_timer(act, t, timer);

	zfcp_erp_notify(act, 0);
}