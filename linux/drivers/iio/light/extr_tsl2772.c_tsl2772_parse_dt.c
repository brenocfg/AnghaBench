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
struct tsl2772_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tsl2772_read_prox_diodes (struct tsl2772_chip*) ; 
 int /*<<< orphan*/  tsl2772_read_prox_led_current (struct tsl2772_chip*) ; 

__attribute__((used)) static void tsl2772_parse_dt(struct tsl2772_chip *chip)
{
	tsl2772_read_prox_led_current(chip);
	tsl2772_read_prox_diodes(chip);
}