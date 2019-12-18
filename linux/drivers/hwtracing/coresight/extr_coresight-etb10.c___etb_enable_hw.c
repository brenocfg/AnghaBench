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
struct etb_drvdata {int buffer_depth; int trigger_cntr; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 int ETB_CTL_CAPT_EN ; 
 scalar_t__ ETB_CTL_REG ; 
 scalar_t__ ETB_FFCR ; 
 int ETB_FFCR_EN_FTC ; 
 int ETB_FFCR_STOP_TRIGGER ; 
 scalar_t__ ETB_RAM_READ_POINTER ; 
 scalar_t__ ETB_RAM_WRITE_POINTER ; 
 scalar_t__ ETB_RWD_REG ; 
 scalar_t__ ETB_TRG ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void __etb_enable_hw(struct etb_drvdata *drvdata)
{
	int i;
	u32 depth;

	CS_UNLOCK(drvdata->base);

	depth = drvdata->buffer_depth;
	/* reset write RAM pointer address */
	writel_relaxed(0x0, drvdata->base + ETB_RAM_WRITE_POINTER);
	/* clear entire RAM buffer */
	for (i = 0; i < depth; i++)
		writel_relaxed(0x0, drvdata->base + ETB_RWD_REG);

	/* reset write RAM pointer address */
	writel_relaxed(0x0, drvdata->base + ETB_RAM_WRITE_POINTER);
	/* reset read RAM pointer address */
	writel_relaxed(0x0, drvdata->base + ETB_RAM_READ_POINTER);

	writel_relaxed(drvdata->trigger_cntr, drvdata->base + ETB_TRG);
	writel_relaxed(ETB_FFCR_EN_FTC | ETB_FFCR_STOP_TRIGGER,
		       drvdata->base + ETB_FFCR);
	/* ETB trace capture enable */
	writel_relaxed(ETB_CTL_CAPT_EN, drvdata->base + ETB_CTL_REG);

	CS_LOCK(drvdata->base);
}