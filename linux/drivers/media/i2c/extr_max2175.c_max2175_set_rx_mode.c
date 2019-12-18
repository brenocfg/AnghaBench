#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct max2175 {scalar_t__ xtal_freq; int mode_resolved; TYPE_4__* i2s_en; TYPE_2__* hsls; scalar_t__ am_hiz; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; } ;
struct TYPE_8__ {TYPE_3__ cur; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
struct TYPE_6__ {TYPE_1__ cur; } ;

/* Variables and functions */
 scalar_t__ MAX2175_EU_XTAL_FREQ ; 
 int /*<<< orphan*/  max2175_i2s_enable (struct max2175*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_set_bbfilter (struct max2175*) ; 
 int /*<<< orphan*/  max2175_set_eu_rx_mode (struct max2175*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_set_hsls (struct max2175*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_set_na_rx_mode (struct max2175*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_write_bit (struct max2175*,int,int,int) ; 
 int /*<<< orphan*/  max2175_write_bits (struct max2175*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,...) ; 

__attribute__((used)) static int max2175_set_rx_mode(struct max2175 *ctx, u32 rx_mode)
{
	mxm_dbg(ctx, "set_rx_mode: %u am_hiz %u\n", rx_mode, ctx->am_hiz);
	if (ctx->xtal_freq == MAX2175_EU_XTAL_FREQ)
		max2175_set_eu_rx_mode(ctx, rx_mode);
	else
		max2175_set_na_rx_mode(ctx, rx_mode);

	if (ctx->am_hiz) {
		mxm_dbg(ctx, "setting AM HiZ related config\n");
		max2175_write_bit(ctx, 50, 5, 1);
		max2175_write_bit(ctx, 90, 7, 1);
		max2175_write_bits(ctx, 73, 1, 0, 2);
		max2175_write_bits(ctx, 80, 5, 0, 33);
	}

	/* Load BB filter trim values saved in ROM */
	max2175_set_bbfilter(ctx);

	/* Set HSLS */
	max2175_set_hsls(ctx, ctx->hsls->cur.val);

	/* Use i2s enable settings */
	max2175_i2s_enable(ctx, ctx->i2s_en->cur.val);

	ctx->mode_resolved = true;

	return 0;
}