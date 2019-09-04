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
struct tegra_dfll {int lut_safe; int cg; } ;
struct dfll_rate_req {int lut_index; int mult_bits; int scale_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLL_FREQ_REQ ; 
 int DFLL_FREQ_REQ_FORCE_ENABLE ; 
 int DFLL_FREQ_REQ_FORCE_MASK ; 
 int DFLL_FREQ_REQ_FORCE_SHIFT ; 
 int DFLL_FREQ_REQ_FREQ_VALID ; 
 int DFLL_FREQ_REQ_MULT_SHIFT ; 
 int DFLL_FREQ_REQ_SCALE_SHIFT ; 
 int /*<<< orphan*/  FORCE_MAX ; 
 int /*<<< orphan*/  FORCE_MIN ; 
 int clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfll_wmb (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_writel (struct tegra_dfll*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dfll_set_frequency_request(struct tegra_dfll *td,
				       struct dfll_rate_req *req)
{
	u32 val = 0;
	int force_val;
	int coef = 128; /* FIXME: td->cg_scale? */;

	force_val = (req->lut_index - td->lut_safe) * coef / td->cg;
	force_val = clamp(force_val, FORCE_MIN, FORCE_MAX);

	val |= req->mult_bits << DFLL_FREQ_REQ_MULT_SHIFT;
	val |= req->scale_bits << DFLL_FREQ_REQ_SCALE_SHIFT;
	val |= ((u32)force_val << DFLL_FREQ_REQ_FORCE_SHIFT) &
		DFLL_FREQ_REQ_FORCE_MASK;
	val |= DFLL_FREQ_REQ_FREQ_VALID | DFLL_FREQ_REQ_FORCE_ENABLE;

	dfll_writel(td, val, DFLL_FREQ_REQ);
	dfll_wmb(td);
}