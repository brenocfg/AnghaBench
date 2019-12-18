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
struct wm831x_irq_data {int dummy; } ;
struct wm831x {int dummy; } ;

/* Variables and functions */
 struct wm831x_irq_data* wm831x_irqs ; 

__attribute__((used)) static inline struct wm831x_irq_data *irq_to_wm831x_irq(struct wm831x *wm831x,
							int irq)
{
	return &wm831x_irqs[irq];
}