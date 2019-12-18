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
struct max2175 {int /*<<< orphan*/  rom_bbf_bw_fm; int /*<<< orphan*/  rom_bbf_bw_dab; int /*<<< orphan*/  rom_bbf_bw_am; } ;

/* Variables and functions */
 scalar_t__ MAX2175_IS_BAND_AM (struct max2175*) ; 
 scalar_t__ MAX2175_IS_DAB_MODE (struct max2175*) ; 
 int /*<<< orphan*/  max2175_write_bits (struct max2175*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max2175_set_bbfilter(struct max2175 *ctx)
{
	if (MAX2175_IS_BAND_AM(ctx)) {
		max2175_write_bits(ctx, 12, 3, 0, ctx->rom_bbf_bw_am);
		mxm_dbg(ctx, "set_bbfilter AM: rom %d\n", ctx->rom_bbf_bw_am);
	} else if (MAX2175_IS_DAB_MODE(ctx)) {
		max2175_write_bits(ctx, 12, 3, 0, ctx->rom_bbf_bw_dab);
		mxm_dbg(ctx, "set_bbfilter DAB: rom %d\n", ctx->rom_bbf_bw_dab);
	} else {
		max2175_write_bits(ctx, 12, 3, 0, ctx->rom_bbf_bw_fm);
		mxm_dbg(ctx, "set_bbfilter FM: rom %d\n", ctx->rom_bbf_bw_fm);
	}
}