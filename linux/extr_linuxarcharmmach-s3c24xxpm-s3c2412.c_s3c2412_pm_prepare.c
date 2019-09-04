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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C2412_PWRCFG ; 
 int /*<<< orphan*/  samsung_sync_wakemask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_irqs ; 

__attribute__((used)) static void s3c2412_pm_prepare(void)
{
	samsung_sync_wakemask(S3C2412_PWRCFG,
			      wake_irqs, ARRAY_SIZE(wake_irqs));
}