#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct zfcp_erp_action {TYPE_1__ timer; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_memwait_handler ; 

__attribute__((used)) static void zfcp_erp_strategy_memwait(struct zfcp_erp_action *erp_action)
{
	timer_setup(&erp_action->timer, zfcp_erp_memwait_handler, 0);
	erp_action->timer.expires = jiffies + HZ;
	add_timer(&erp_action->timer);
}