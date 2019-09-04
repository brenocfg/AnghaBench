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
struct tpiu_drvdata {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 int FFCR_FON_MAN ; 
 int /*<<< orphan*/  FFCR_FON_MAN_BIT ; 
 int FFCR_STOP_FI ; 
 int /*<<< orphan*/  FFSR_FT_STOPPED_BIT ; 
 scalar_t__ TPIU_FFCR ; 
 scalar_t__ TPIU_FFSR ; 
 int /*<<< orphan*/  coresight_timeout (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void tpiu_disable_hw(struct tpiu_drvdata *drvdata)
{
	CS_UNLOCK(drvdata->base);

	/* Clear formatter and stop on flush */
	writel_relaxed(FFCR_STOP_FI, drvdata->base + TPIU_FFCR);
	/* Generate manual flush */
	writel_relaxed(FFCR_STOP_FI | FFCR_FON_MAN, drvdata->base + TPIU_FFCR);
	/* Wait for flush to complete */
	coresight_timeout(drvdata->base, TPIU_FFCR, FFCR_FON_MAN_BIT, 0);
	/* Wait for formatter to stop */
	coresight_timeout(drvdata->base, TPIU_FFSR, FFSR_FT_STOPPED_BIT, 1);

	CS_LOCK(drvdata->base);
}