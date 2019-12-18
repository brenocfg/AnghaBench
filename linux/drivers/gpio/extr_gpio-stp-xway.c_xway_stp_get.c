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
struct xway_stp {int /*<<< orphan*/  virt; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  XWAY_STP_CPU0 ; 
 struct xway_stp* gpiochip_get_data (struct gpio_chip*) ; 
 int xway_stp_r32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xway_stp_get(struct gpio_chip *gc, unsigned int gpio)
{
	struct xway_stp *chip = gpiochip_get_data(gc);

	return (xway_stp_r32(chip->virt, XWAY_STP_CPU0) & BIT(gpio));
}