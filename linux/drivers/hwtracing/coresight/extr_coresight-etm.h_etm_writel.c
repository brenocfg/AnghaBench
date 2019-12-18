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
typedef  scalar_t__ u32 ;
struct etm_drvdata {scalar_t__ base; TYPE_1__* csdev; scalar_t__ use_cp14; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ etm_writel_cp14 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void etm_writel(struct etm_drvdata *drvdata,
			      u32 val, u32 off)
{
	if (drvdata->use_cp14) {
		if (etm_writel_cp14(off, val)) {
			dev_err(&drvdata->csdev->dev,
				"invalid CP14 access to ETM reg: %#x", off);
		}
	} else {
		writel_relaxed(val, drvdata->base + off);
	}
}