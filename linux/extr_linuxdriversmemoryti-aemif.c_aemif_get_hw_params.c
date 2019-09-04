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
struct platform_device {int dummy; } ;
struct aemif_device {unsigned long clk_rate; int cs_offset; int base; struct aemif_cs_data* cs_data; } ;
struct aemif_cs_data {int cs; int asize; int /*<<< orphan*/  enable_ss; int /*<<< orphan*/  enable_ew; void* wsetup; void* wstrobe; void* whold; void* rsetup; void* rstrobe; void* rhold; void* ta; } ;

/* Variables and functions */
 int A1CR_OFFSET ; 
 int ASIZE_MAX ; 
 int /*<<< orphan*/  EW_VAL (int) ; 
 int /*<<< orphan*/  RHOLD_VAL (int) ; 
 int /*<<< orphan*/  RSETUP_VAL (int) ; 
 int /*<<< orphan*/  RSTROBE_VAL (int) ; 
 int /*<<< orphan*/  SS_VAL (int) ; 
 int /*<<< orphan*/  TA_VAL (int) ; 
 int /*<<< orphan*/  WHOLD_VAL (int) ; 
 int /*<<< orphan*/  WSETUP_VAL (int) ; 
 int /*<<< orphan*/  WSTROBE_VAL (int) ; 
 void* aemif_cycles_to_nsec (int /*<<< orphan*/ ,unsigned long) ; 
 struct aemif_device* platform_get_drvdata (struct platform_device*) ; 
 int readl (int) ; 

__attribute__((used)) static void aemif_get_hw_params(struct platform_device *pdev, int csnum)
{
	struct aemif_device *aemif = platform_get_drvdata(pdev);
	struct aemif_cs_data *data = &aemif->cs_data[csnum];
	unsigned long clk_rate = aemif->clk_rate;
	u32 val, offset;

	offset = A1CR_OFFSET + (data->cs - aemif->cs_offset) * 4;
	val = readl(aemif->base + offset);

	data->ta = aemif_cycles_to_nsec(TA_VAL(val), clk_rate);
	data->rhold = aemif_cycles_to_nsec(RHOLD_VAL(val), clk_rate);
	data->rstrobe = aemif_cycles_to_nsec(RSTROBE_VAL(val), clk_rate);
	data->rsetup = aemif_cycles_to_nsec(RSETUP_VAL(val), clk_rate);
	data->whold = aemif_cycles_to_nsec(WHOLD_VAL(val), clk_rate);
	data->wstrobe = aemif_cycles_to_nsec(WSTROBE_VAL(val), clk_rate);
	data->wsetup = aemif_cycles_to_nsec(WSETUP_VAL(val), clk_rate);
	data->enable_ew = EW_VAL(val);
	data->enable_ss = SS_VAL(val);
	data->asize = val & ASIZE_MAX;
}