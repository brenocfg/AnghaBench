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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct lpi2c_imx_struct {TYPE_1__ adapter; scalar_t__ base; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 scalar_t__ LPI2C_MFSR ; 
 scalar_t__ LPI2C_MSR ; 
 int MSR_NDF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static int lpi2c_imx_txfifo_empty(struct lpi2c_imx_struct *lpi2c_imx)
{
	unsigned long orig_jiffies = jiffies;
	u32 txcnt;

	do {
		txcnt = readl(lpi2c_imx->base + LPI2C_MFSR) & 0xff;

		if (readl(lpi2c_imx->base + LPI2C_MSR) & MSR_NDF) {
			dev_dbg(&lpi2c_imx->adapter.dev, "NDF detected\n");
			return -EIO;
		}

		if (time_after(jiffies, orig_jiffies + msecs_to_jiffies(500))) {
			dev_dbg(&lpi2c_imx->adapter.dev, "txfifo empty timeout\n");
			return -ETIMEDOUT;
		}
		schedule();

	} while (txcnt);

	return 0;
}