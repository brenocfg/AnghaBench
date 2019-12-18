#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wl1251 {TYPE_1__* if_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_irq ) (struct wl1251*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wl1251*) ; 

void wl1251_enable_interrupts(struct wl1251 *wl)
{
	wl->if_ops->enable_irq(wl);
}