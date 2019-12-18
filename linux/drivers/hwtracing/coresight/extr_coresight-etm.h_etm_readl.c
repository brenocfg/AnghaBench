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
typedef  unsigned int u32 ;
struct etm_drvdata {unsigned int base; TYPE_1__* csdev; scalar_t__ use_cp14; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 scalar_t__ etm_readl_cp14 (unsigned int,unsigned int*) ; 
 unsigned int readl_relaxed (unsigned int) ; 

__attribute__((used)) static inline unsigned int etm_readl(struct etm_drvdata *drvdata, u32 off)
{
	u32 val;

	if (drvdata->use_cp14) {
		if (etm_readl_cp14(off, &val)) {
			dev_err(&drvdata->csdev->dev,
				"invalid CP14 access to ETM reg: %#x", off);
		}
	} else {
		val = readl_relaxed(drvdata->base + off);
	}

	return val;
}