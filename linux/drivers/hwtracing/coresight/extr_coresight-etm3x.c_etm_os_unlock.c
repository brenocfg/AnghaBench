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
struct etm_drvdata {int os_unlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETMOSLAR ; 
 int /*<<< orphan*/  etm_writel (struct etm_drvdata*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isb () ; 

__attribute__((used)) static void etm_os_unlock(struct etm_drvdata *drvdata)
{
	/* Writing any value to ETMOSLAR unlocks the trace registers */
	etm_writel(drvdata, 0x0, ETMOSLAR);
	drvdata->os_unlock = true;
	isb();
}