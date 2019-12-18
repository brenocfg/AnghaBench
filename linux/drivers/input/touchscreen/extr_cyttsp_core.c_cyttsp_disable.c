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
struct cyttsp {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CY_LOW_POWER_MODE ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int ttsp_send_command (struct cyttsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyttsp_disable(struct cyttsp *ts)
{
	int error;

	error = ttsp_send_command(ts, CY_LOW_POWER_MODE);
	if (error)
		return error;

	disable_irq(ts->irq);

	return 0;
}