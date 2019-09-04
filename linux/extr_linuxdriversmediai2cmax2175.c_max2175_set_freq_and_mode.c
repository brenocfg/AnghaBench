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
struct max2175 {TYPE_4__* hsls; TYPE_2__* rx_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; } ;
struct TYPE_8__ {TYPE_3__ cur; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
struct TYPE_6__ {TYPE_1__ cur; } ;

/* Variables and functions */
 int max2175_rx_mode_from_freq (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max2175_set_rx_mode (struct max2175*,int /*<<< orphan*/ ) ; 
 int max2175_tune_rf_freq (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max2175_set_freq_and_mode(struct max2175 *ctx, u32 freq)
{
	u32 rx_mode;
	int ret;

	/* Get band from frequency */
	ret = max2175_rx_mode_from_freq(ctx, freq, &rx_mode);
	if (ret)
		return ret;

	mxm_dbg(ctx, "set_freq_and_mode: freq %u rx_mode %d\n", freq, rx_mode);

	/* Load mode */
	max2175_set_rx_mode(ctx, rx_mode);
	ctx->rx_mode->cur.val = rx_mode;

	/* Tune to the new freq given */
	return max2175_tune_rf_freq(ctx, freq, ctx->hsls->cur.val);
}