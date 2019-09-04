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
 int EAGAIN ; 
 int ETIMEDOUT ; 
 scalar_t__ LPI2C_MSR ; 
 unsigned int MSR_ALF ; 
 unsigned int MSR_BBF ; 
 unsigned int MSR_MBF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int lpi2c_imx_bus_busy(struct lpi2c_imx_struct *lpi2c_imx)
{
	unsigned long orig_jiffies = jiffies;
	unsigned int temp;

	while (1) {
		temp = readl(lpi2c_imx->base + LPI2C_MSR);

		/* check for arbitration lost, clear if set */
		if (temp & MSR_ALF) {
			writel(temp, lpi2c_imx->base + LPI2C_MSR);
			return -EAGAIN;
		}

		if (temp & (MSR_BBF | MSR_MBF))
			break;

		if (time_after(jiffies, orig_jiffies + msecs_to_jiffies(500))) {
			dev_dbg(&lpi2c_imx->adapter.dev, "bus not work\n");
			return -ETIMEDOUT;
		}
		schedule();
	}

	return 0;
}