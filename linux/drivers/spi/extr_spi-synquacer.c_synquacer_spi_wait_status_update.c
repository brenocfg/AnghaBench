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
typedef  int u32 ;
struct synquacer_spi {int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SYNQUACER_HSSPI_ENABLE_TMOUT_MSEC ; 
 int SYNQUACER_HSSPI_MCTRL_MES ; 
 scalar_t__ SYNQUACER_HSSPI_REG_MCTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int synquacer_spi_wait_status_update(struct synquacer_spi *sspi,
					    bool enable)
{
	u32 val;
	unsigned long timeout = jiffies +
		msecs_to_jiffies(SYNQUACER_HSSPI_ENABLE_TMOUT_MSEC);

	/* wait MES(Module Enable Status) is updated */
	do {
		val = readl(sspi->regs + SYNQUACER_HSSPI_REG_MCTRL) &
		      SYNQUACER_HSSPI_MCTRL_MES;
		if (enable && val)
			return 0;
		if (!enable && !val)
			return 0;
	} while (time_before(jiffies, timeout));

	dev_err(sspi->dev, "timeout occurs in updating Module Enable Status\n");
	return -EBUSY;
}