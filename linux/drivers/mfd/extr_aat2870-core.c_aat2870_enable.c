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
struct aat2870_data {scalar_t__ en_pin; int is_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (scalar_t__,int) ; 

__attribute__((used)) static inline void aat2870_enable(struct aat2870_data *aat2870)
{
	if (aat2870->en_pin >= 0)
		gpio_set_value(aat2870->en_pin, 1);

	aat2870->is_enable = 1;
}