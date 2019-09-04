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
typedef  int const uint32_t ;
struct gpio_service {int** busyness; } ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;

/* Variables and functions */

__attribute__((used)) static bool is_pin_busy(
	const struct gpio_service *service,
	enum gpio_id id,
	uint32_t en)
{
	const uint32_t bits_per_uint = sizeof(uint32_t) << 3;

	const uint32_t *slot = service->busyness[id] + (en / bits_per_uint);

	return 0 != (*slot & (1 << (en % bits_per_uint)));
}