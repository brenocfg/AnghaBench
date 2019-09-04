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

__attribute__((used)) static unsigned long s3c24xx_read_idcode_v5(void)
{
#if defined(CONFIG_CPU_S3C2416)
	/* s3c2416 is v5, with S3C24XX_GSTATUS1 instead of S3C2412_GSTATUS1 */

	u32 gs = __raw_readl(S3C24XX_GSTATUS1);

	/* test for s3c2416 or similar device */
	if ((gs >> 16) == 0x3245)
		return gs;
#endif

#if defined(CONFIG_CPU_S3C2412)
	return __raw_readl(S3C2412_GSTATUS1);
#else
	return 1UL;	/* don't look like an 2400 */
#endif
}