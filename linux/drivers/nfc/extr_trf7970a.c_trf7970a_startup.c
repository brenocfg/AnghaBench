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
struct trf7970a {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ ) ; 
 int trf7970a_power_up (struct trf7970a*) ; 

__attribute__((used)) static int trf7970a_startup(struct trf7970a *trf)
{
	int ret;

	ret = trf7970a_power_up(trf);
	if (ret)
		return ret;

	pm_runtime_set_active(trf->dev);
	pm_runtime_enable(trf->dev);
	pm_runtime_mark_last_busy(trf->dev);

	return 0;
}