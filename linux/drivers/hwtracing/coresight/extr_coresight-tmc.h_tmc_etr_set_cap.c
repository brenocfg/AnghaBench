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
typedef  int /*<<< orphan*/  u32 ;
struct tmc_drvdata {int /*<<< orphan*/  etr_caps; } ;

/* Variables and functions */

__attribute__((used)) static inline void tmc_etr_set_cap(struct tmc_drvdata *drvdata, u32 cap)
{
	drvdata->etr_caps |= cap;
}