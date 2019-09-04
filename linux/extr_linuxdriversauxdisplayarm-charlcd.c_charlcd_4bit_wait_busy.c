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
struct charlcd {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ charlcd_4bit_read_bf (struct charlcd*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void charlcd_4bit_wait_busy(struct charlcd *lcd)
{
	int retries = 50;

	udelay(100);
	while (charlcd_4bit_read_bf(lcd) && retries)
		retries--;
	if (!retries)
		dev_err(lcd->dev, "timeout waiting for busyflag\n");
}