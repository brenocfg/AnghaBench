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
struct tca6416_keypad_chip {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  tca6416_keys_scan (struct tca6416_keypad_chip*) ; 

__attribute__((used)) static irqreturn_t tca6416_keys_isr(int irq, void *dev_id)
{
	struct tca6416_keypad_chip *chip = dev_id;

	tca6416_keys_scan(chip);

	return IRQ_HANDLED;
}