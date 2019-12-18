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
struct etm_drvdata {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EAGAIN ; 
 int TIMEOUT_US ; 
 int etm_readl (struct etm_drvdata*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int coresight_timeout_etm(struct etm_drvdata *drvdata, u32 offset,
				  int position, int value)
{
	int i;
	u32 val;

	for (i = TIMEOUT_US; i > 0; i--) {
		val = etm_readl(drvdata, offset);
		/* Waiting on the bit to go from 0 to 1 */
		if (value) {
			if (val & BIT(position))
				return 0;
		/* Waiting on the bit to go from 1 to 0 */
		} else {
			if (!(val & BIT(position)))
				return 0;
		}

		/*
		 * Delay is arbitrary - the specification doesn't say how long
		 * we are expected to wait.  Extra check required to make sure
		 * we don't wait needlessly on the last iteration.
		 */
		if (i - 1)
			udelay(1);
	}

	return -EAGAIN;
}