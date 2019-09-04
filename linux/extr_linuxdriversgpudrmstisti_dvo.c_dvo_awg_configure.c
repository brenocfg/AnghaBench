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
struct sti_dvo {scalar_t__ regs; } ;

/* Variables and functions */
 int AWG_MAX_INST ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DVO_AWG_CTRL_EN ; 
 scalar_t__ DVO_AWG_DIGSYNC_CTRL ; 
 scalar_t__ DVO_DIGSYNC_INSTR_I ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dvo_awg_configure(struct sti_dvo *dvo, u32 *awg_ram_code, int nb)
{
	int i;

	DRM_DEBUG_DRIVER("\n");

	for (i = 0; i < nb; i++)
		writel(awg_ram_code[i],
		       dvo->regs + DVO_DIGSYNC_INSTR_I + i * 4);
	for (i = nb; i < AWG_MAX_INST; i++)
		writel(0, dvo->regs + DVO_DIGSYNC_INSTR_I + i * 4);

	writel(DVO_AWG_CTRL_EN, dvo->regs + DVO_AWG_DIGSYNC_CTRL);
}