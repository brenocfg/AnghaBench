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
struct sprd_adi {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int ADI_FIFO_DRAIN_TIMEOUT ; 
 int BIT_FIFO_EMPTY ; 
 int EBUSY ; 
 scalar_t__ REG_ADI_ARM_FIFO_STS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int sprd_adi_drain_fifo(struct sprd_adi *sadi)
{
	u32 timeout = ADI_FIFO_DRAIN_TIMEOUT;
	u32 sts;

	do {
		sts = readl_relaxed(sadi->base + REG_ADI_ARM_FIFO_STS);
		if (sts & BIT_FIFO_EMPTY)
			break;

		cpu_relax();
	} while (--timeout);

	if (timeout == 0) {
		dev_err(sadi->dev, "drain write fifo timeout\n");
		return -EBUSY;
	}

	return 0;
}