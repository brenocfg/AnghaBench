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
struct cbus_host {int /*<<< orphan*/  clk; int /*<<< orphan*/  dat; } ;

/* Variables and functions */
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cbus_receive_bit(struct cbus_host *host)
{
	int ret;

	gpiod_set_value(host->clk, 1);
	ret = gpiod_get_value(host->dat);
	gpiod_set_value(host->clk, 0);
	return ret;
}