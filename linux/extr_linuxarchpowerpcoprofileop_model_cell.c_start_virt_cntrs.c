#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  cell_virtual_cntr ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ timer_virt_cntr ; 

__attribute__((used)) static void start_virt_cntrs(void)
{
	timer_setup(&timer_virt_cntr, cell_virtual_cntr, 0);
	timer_virt_cntr.expires = jiffies + HZ / 10;
	add_timer(&timer_virt_cntr);
}