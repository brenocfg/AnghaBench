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
struct sta_info {int /*<<< orphan*/  addba_retry_timer; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  addba_timer_hdl ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void init_addba_retry_timer(struct adapter *padapter, struct sta_info *psta)
{
	timer_setup(&psta->addba_retry_timer, addba_timer_hdl, 0);
}