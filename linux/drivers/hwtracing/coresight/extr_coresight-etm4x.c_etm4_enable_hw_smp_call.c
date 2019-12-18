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
struct etm4_enable_arg {int /*<<< orphan*/  drvdata; int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  etm4_enable_hw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etm4_enable_hw_smp_call(void *info)
{
	struct etm4_enable_arg *arg = info;

	if (WARN_ON(!arg))
		return;
	arg->rc = etm4_enable_hw(arg->drvdata);
}