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
struct st95hf_context {int /*<<< orphan*/  enable_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIGH ; 
 int /*<<< orphan*/  LOW ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void st95hf_send_st95enable_negativepulse(struct st95hf_context *st95con)
{
	/* First make irq_in pin high */
	gpio_set_value(st95con->enable_gpio, HIGH);

	/* wait for 1 milisecond */
	usleep_range(1000, 2000);

	/* Make irq_in pin low */
	gpio_set_value(st95con->enable_gpio, LOW);

	/* wait for minimum interrupt pulse to make st95 active */
	usleep_range(1000, 2000);

	/* At end make it high */
	gpio_set_value(st95con->enable_gpio, HIGH);
}