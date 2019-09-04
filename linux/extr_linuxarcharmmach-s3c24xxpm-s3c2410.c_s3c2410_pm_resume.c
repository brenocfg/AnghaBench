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
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  S3C2410_GPF (int) ; 
 int /*<<< orphan*/  S3C2410_GSTATUS2 ; 
 unsigned long S3C2410_GSTATUS2_OFFRESET ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ machine_is_aml_m5900 () ; 

__attribute__((used)) static void s3c2410_pm_resume(void)
{
	unsigned long tmp;

	/* unset the return-from-sleep flag, to ensure reset */

	tmp = __raw_readl(S3C2410_GSTATUS2);
	tmp &= S3C2410_GSTATUS2_OFFRESET;
	__raw_writel(tmp, S3C2410_GSTATUS2);

	if (machine_is_aml_m5900()) {
		gpio_request_one(S3C2410_GPF(2), GPIOF_OUT_INIT_LOW, NULL);
		gpio_free(S3C2410_GPF(2));
	}
}