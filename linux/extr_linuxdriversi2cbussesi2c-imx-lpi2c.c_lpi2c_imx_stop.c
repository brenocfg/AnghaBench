#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct lpi2c_imx_struct {TYPE_1__ adapter; scalar_t__ base; } ;

/* Variables and functions */
 int GEN_STOP ; 
 scalar_t__ LPI2C_MSR ; 
 scalar_t__ LPI2C_MTDR ; 
 unsigned int MSR_SDF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void lpi2c_imx_stop(struct lpi2c_imx_struct *lpi2c_imx)
{
	unsigned long orig_jiffies = jiffies;
	unsigned int temp;

	writel(GEN_STOP << 8, lpi2c_imx->base + LPI2C_MTDR);

	do {
		temp = readl(lpi2c_imx->base + LPI2C_MSR);
		if (temp & MSR_SDF)
			break;

		if (time_after(jiffies, orig_jiffies + msecs_to_jiffies(500))) {
			dev_dbg(&lpi2c_imx->adapter.dev, "stop timeout\n");
			break;
		}
		schedule();

	} while (1);
}