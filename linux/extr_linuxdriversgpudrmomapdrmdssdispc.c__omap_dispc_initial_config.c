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
typedef  int /*<<< orphan*/  u32 ;
struct dispc_device {TYPE_1__* feat; int /*<<< orphan*/  core_clk_rate; } ;
struct TYPE_2__ {scalar_t__ mstandby_workaround; scalar_t__ has_gamma_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONFIG ; 
 int /*<<< orphan*/  DISPC_DIVISOR ; 
 int /*<<< orphan*/  DISPC_MSTANDBY_CTRL ; 
 int /*<<< orphan*/  FEAT_CORE_CLK_DIV ; 
 int /*<<< orphan*/  FEAT_FUNCGATED ; 
 int /*<<< orphan*/  FEAT_MFLAG ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  OMAP_DSS_LOAD_FRAME_ONLY ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dispc_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dispc_configure_burst_sizes (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_fclk_rate (struct dispc_device*) ; 
 scalar_t__ dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_init_fifos (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_init_mflag (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_ovl_enable_zorder_planes (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_read_reg (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_set_loadmode (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_setup_color_conv_coef (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _omap_dispc_initial_config(struct dispc_device *dispc)
{
	u32 l;

	/* Exclusively enable DISPC_CORE_CLK and set divider to 1 */
	if (dispc_has_feature(dispc, FEAT_CORE_CLK_DIV)) {
		l = dispc_read_reg(dispc, DISPC_DIVISOR);
		/* Use DISPC_DIVISOR.LCD, instead of DISPC_DIVISOR1.LCD */
		l = FLD_MOD(l, 1, 0, 0);
		l = FLD_MOD(l, 1, 23, 16);
		dispc_write_reg(dispc, DISPC_DIVISOR, l);

		dispc->core_clk_rate = dispc_fclk_rate(dispc);
	}

	/* Use gamma table mode, instead of palette mode */
	if (dispc->feat->has_gamma_table)
		REG_FLD_MOD(dispc, DISPC_CONFIG, 1, 3, 3);

	/* For older DSS versions (FEAT_FUNCGATED) this enables
	 * func-clock auto-gating. For newer versions
	 * (dispc->feat->has_gamma_table) this enables tv-out gamma tables.
	 */
	if (dispc_has_feature(dispc, FEAT_FUNCGATED) ||
	    dispc->feat->has_gamma_table)
		REG_FLD_MOD(dispc, DISPC_CONFIG, 1, 9, 9);

	dispc_setup_color_conv_coef(dispc);

	dispc_set_loadmode(dispc, OMAP_DSS_LOAD_FRAME_ONLY);

	dispc_init_fifos(dispc);

	dispc_configure_burst_sizes(dispc);

	dispc_ovl_enable_zorder_planes(dispc);

	if (dispc->feat->mstandby_workaround)
		REG_FLD_MOD(dispc, DISPC_MSTANDBY_CTRL, 1, 0, 0);

	if (dispc_has_feature(dispc, FEAT_MFLAG))
		dispc_init_mflag(dispc);
}