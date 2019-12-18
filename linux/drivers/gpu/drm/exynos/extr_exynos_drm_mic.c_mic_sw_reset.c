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
struct exynos_mic {scalar_t__ reg; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ MIC_OP ; 
 int MIC_SW_RST ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mic_sw_reset(struct exynos_mic *mic)
{
	unsigned int retry = 100;
	int ret;

	writel(MIC_SW_RST, mic->reg + MIC_OP);

	while (retry-- > 0) {
		ret = readl(mic->reg + MIC_OP);
		if (!(ret & MIC_SW_RST))
			return 0;

		udelay(10);
	}

	return -ETIMEDOUT;
}