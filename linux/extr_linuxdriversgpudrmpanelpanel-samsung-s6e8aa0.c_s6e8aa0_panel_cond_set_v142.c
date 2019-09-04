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
typedef  int u8 ;
struct s6e8aa0 {int id; scalar_t__ flip_vertical; scalar_t__ flip_horizontal; } ;

/* Variables and functions */
 int PANELCTL_BICTLB_001 ; 
 int PANELCTL_BICTLB_CON_MASK ; 
 int PANELCTL_BICTL_000 ; 
 int PANELCTL_BICTL_CON_MASK ; 
 int PANELCTL_CLK1_000 ; 
 int PANELCTL_CLK1_CON_MASK ; 
 int PANELCTL_CLK2_001 ; 
 int PANELCTL_CLK2_CON_MASK ; 
 int PANELCTL_EM_CLK1B_110 ; 
 int PANELCTL_EM_CLK1B_CON_MASK ; 
 int PANELCTL_EM_CLK1_110 ; 
 int PANELCTL_EM_CLK1_CON_MASK ; 
 int PANELCTL_EM_CLK2B_110 ; 
 int PANELCTL_EM_CLK2B_CON_MASK ; 
 int PANELCTL_EM_CLK2_110 ; 
 int PANELCTL_EM_CLK2_CON_MASK ; 
 int PANELCTL_EM_INT1_000 ; 
 int PANELCTL_EM_INT1_CON_MASK ; 
 int PANELCTL_EM_INT2_001 ; 
 int PANELCTL_EM_INT2_CON_MASK ; 
 int PANELCTL_GTCON_110 ; 
 int PANELCTL_GTCON_MASK ; 
 int PANELCTL_INT1_000 ; 
 int PANELCTL_INT1_CON_MASK ; 
 int PANELCTL_INT2_001 ; 
 int PANELCTL_INT2_CON_MASK ; 
 int PANELCTL_SS_1_800 ; 
 int PANELCTL_SS_MASK ; 
 int /*<<< orphan*/  s6e8aa0_dcs_write_seq (struct s6e8aa0*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void s6e8aa0_panel_cond_set_v142(struct s6e8aa0 *ctx)
{
	static const u8 aids[] = {
		0x04, 0x04, 0x04, 0x04, 0x04, 0x60, 0x80, 0xA0
	};
	u8 aid = aids[ctx->id >> 5];
	u8 cfg = 0x3d;
	u8 clk_con = 0xc8;
	u8 int_con = 0x08;
	u8 bictl_con = 0x48;
	u8 em_clk1_con = 0xff;
	u8 em_clk2_con = 0xff;
	u8 em_int_con = 0xc8;

	if (ctx->flip_vertical) {
		/* GTCON */
		cfg &= ~(PANELCTL_GTCON_MASK);
		cfg |= (PANELCTL_GTCON_110);
	}

	if (ctx->flip_horizontal) {
		/* SS */
		cfg &= ~(PANELCTL_SS_MASK);
		cfg |= (PANELCTL_SS_1_800);
	}

	if (ctx->flip_horizontal || ctx->flip_vertical) {
		/* CLK1,2_CON */
		clk_con &= ~(PANELCTL_CLK1_CON_MASK |
			PANELCTL_CLK2_CON_MASK);
		clk_con |= (PANELCTL_CLK1_000 | PANELCTL_CLK2_001);

		/* INT1,2_CON */
		int_con &= ~(PANELCTL_INT1_CON_MASK |
			PANELCTL_INT2_CON_MASK);
		int_con |= (PANELCTL_INT1_000 | PANELCTL_INT2_001);

		/* BICTL,B_CON */
		bictl_con &= ~(PANELCTL_BICTL_CON_MASK |
			PANELCTL_BICTLB_CON_MASK);
		bictl_con |= (PANELCTL_BICTL_000 |
			PANELCTL_BICTLB_001);

		/* EM_CLK1,1B_CON */
		em_clk1_con &= ~(PANELCTL_EM_CLK1_CON_MASK |
			PANELCTL_EM_CLK1B_CON_MASK);
		em_clk1_con |= (PANELCTL_EM_CLK1_110 |
			PANELCTL_EM_CLK1B_110);

		/* EM_CLK2,2B_CON */
		em_clk2_con &= ~(PANELCTL_EM_CLK2_CON_MASK |
			PANELCTL_EM_CLK2B_CON_MASK);
		em_clk2_con |= (PANELCTL_EM_CLK2_110 |
			PANELCTL_EM_CLK2B_110);

		/* EM_INT1,2_CON */
		em_int_con &= ~(PANELCTL_EM_INT1_CON_MASK |
			PANELCTL_EM_INT2_CON_MASK);
		em_int_con |= (PANELCTL_EM_INT1_000 |
			PANELCTL_EM_INT2_001);
	}

	s6e8aa0_dcs_write_seq(ctx,
		0xf8, cfg, 0x35, 0x00, 0x00, 0x00, 0x93, 0x00,
		0x3c, 0x78, 0x08, 0x27, 0x7d, 0x3f, 0x00, 0x00,
		0x00, 0x20, aid, 0x08, 0x6e, 0x00, 0x00, 0x00,
		0x02, 0x07, 0x07, 0x23, 0x23, 0xc0, clk_con, int_con,
		bictl_con, 0xc1, 0x00, 0xc1, em_clk1_con, em_clk2_con,
		em_int_con);
}