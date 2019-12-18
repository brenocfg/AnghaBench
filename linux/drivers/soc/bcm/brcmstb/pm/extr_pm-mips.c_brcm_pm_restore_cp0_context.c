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
struct brcm_pm_s3_context {int /*<<< orphan*/ * cp0_regs; int /*<<< orphan*/  sc_boot_vec; } ;

/* Variables and functions */
 size_t BOOT_VEC ; 
 size_t COMPARE ; 
 size_t CONFIG ; 
 size_t CONTEXT ; 
 size_t EBASE ; 
 size_t EDSP ; 
 size_t HWRENA ; 
 size_t MODE ; 
 size_t PGMK ; 
 size_t STATUS ; 
 size_t USER_LOCAL ; 
 int /*<<< orphan*/  bmips_write_zscm_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_brcm_bootvec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_brcm_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_brcm_edsp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_brcm_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_compare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_ebase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_pagemask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_userlocal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcm_pm_restore_cp0_context(struct brcm_pm_s3_context *ctx)
{
	/* Restore cp0 state */
	bmips_write_zscm_reg(0xa0, ctx->sc_boot_vec);

	/* Generic MIPS */
	write_c0_context(ctx->cp0_regs[CONTEXT]);
	write_c0_userlocal(ctx->cp0_regs[USER_LOCAL]);
	write_c0_pagemask(ctx->cp0_regs[PGMK]);
	write_c0_cache(ctx->cp0_regs[HWRENA]);
	write_c0_compare(ctx->cp0_regs[COMPARE]);
	write_c0_status(ctx->cp0_regs[STATUS]);

	/* Broadcom specific */
	write_c0_brcm_config(ctx->cp0_regs[CONFIG]);
	write_c0_brcm_mode(ctx->cp0_regs[MODE]);
	write_c0_brcm_edsp(ctx->cp0_regs[EDSP]);
	write_c0_brcm_bootvec(ctx->cp0_regs[BOOT_VEC]);
	write_c0_ebase(ctx->cp0_regs[EBASE]);
}