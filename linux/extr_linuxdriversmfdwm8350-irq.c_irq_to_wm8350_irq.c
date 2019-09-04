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
struct wm8350_irq_data {int dummy; } ;
struct wm8350 {int irq_base; } ;

/* Variables and functions */
 struct wm8350_irq_data* wm8350_irqs ; 

__attribute__((used)) static inline struct wm8350_irq_data *irq_to_wm8350_irq(struct wm8350 *wm8350,
							int irq)
{
	return &wm8350_irqs[irq - wm8350->irq_base];
}