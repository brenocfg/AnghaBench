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
struct wm831x_irq_data {int reg; } ;

/* Variables and functions */
 int WM831X_INTERRUPT_STATUS_1 ; 

__attribute__((used)) static inline int irq_data_to_status_reg(struct wm831x_irq_data *irq_data)
{
	return WM831X_INTERRUPT_STATUS_1 - 1 + irq_data->reg;
}