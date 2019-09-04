#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } ;
struct max2175 {TYPE_5__* rx_mode; scalar_t__ mode_resolved; int /*<<< orphan*/  freq; TYPE_3__* hsls; TYPE_1__* bands_rf; } ;
struct TYPE_9__ {int /*<<< orphan*/  val; } ;
struct TYPE_10__ {TYPE_4__ cur; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; } ;
struct TYPE_8__ {TYPE_2__ cur; } ;
struct TYPE_6__ {int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max2175_freq_rx_mode_valid (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max2175* max2175_from_sd (struct v4l2_subdev*) ; 
 int max2175_set_freq_and_mode (struct max2175*,int /*<<< orphan*/ ) ; 
 int max2175_tune_rf_freq (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,int,int /*<<< orphan*/ ,scalar_t__,...) ; 

__attribute__((used)) static int max2175_s_frequency(struct v4l2_subdev *sd,
			       const struct v4l2_frequency *vf)
{
	struct max2175 *ctx = max2175_from_sd(sd);
	u32 freq;
	int ret = 0;

	mxm_dbg(ctx, "s_freq: new %u curr %u, mode_resolved %d\n",
		vf->frequency, ctx->freq, ctx->mode_resolved);

	if (vf->tuner != 0)
		return -EINVAL;

	freq = clamp(vf->frequency, ctx->bands_rf->rangelow,
		     ctx->bands_rf->rangehigh);

	/* Check new freq valid for rx_mode if already resolved */
	if (ctx->mode_resolved &&
	    max2175_freq_rx_mode_valid(ctx, ctx->rx_mode->cur.val, freq))
		ret = max2175_tune_rf_freq(ctx, freq, ctx->hsls->cur.val);
	else
		/* Find default rx_mode for freq and tune to it */
		ret = max2175_set_freq_and_mode(ctx, freq);

	mxm_dbg(ctx, "s_freq: ret %d curr %u mode_resolved %d mode %u\n",
		ret, ctx->freq, ctx->mode_resolved, ctx->rx_mode->cur.val);

	return ret;
}