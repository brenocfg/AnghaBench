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
struct bma150_data {TYPE_1__* client; } ;
struct bma150_cfg {int /*<<< orphan*/  lg_thres; int /*<<< orphan*/  lg_dur; int /*<<< orphan*/  lg_hyst; int /*<<< orphan*/  lg_int; int /*<<< orphan*/  hg_thres; int /*<<< orphan*/  hg_dur; int /*<<< orphan*/  hg_hyst; int /*<<< orphan*/  hg_int; int /*<<< orphan*/  any_motion_thres; int /*<<< orphan*/  any_motion_dur; int /*<<< orphan*/  any_motion_int; int /*<<< orphan*/  range; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMA150_MODE_SLEEP ; 
 int bma150_set_any_motion_interrupt (struct bma150_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bma150_set_bandwidth (struct bma150_data*,int /*<<< orphan*/ ) ; 
 int bma150_set_high_g_interrupt (struct bma150_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bma150_set_low_g_interrupt (struct bma150_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bma150_set_mode (struct bma150_data*,int /*<<< orphan*/ ) ; 
 int bma150_set_range (struct bma150_data*,int /*<<< orphan*/ ) ; 
 int bma150_soft_reset (struct bma150_data*) ; 

__attribute__((used)) static int bma150_initialize(struct bma150_data *bma150,
				       const struct bma150_cfg *cfg)
{
	int error;

	error = bma150_soft_reset(bma150);
	if (error)
		return error;

	error = bma150_set_bandwidth(bma150, cfg->bandwidth);
	if (error)
		return error;

	error = bma150_set_range(bma150, cfg->range);
	if (error)
		return error;

	if (bma150->client->irq) {
		error = bma150_set_any_motion_interrupt(bma150,
					cfg->any_motion_int,
					cfg->any_motion_dur,
					cfg->any_motion_thres);
		if (error)
			return error;

		error = bma150_set_high_g_interrupt(bma150,
					cfg->hg_int, cfg->hg_hyst,
					cfg->hg_dur, cfg->hg_thres);
		if (error)
			return error;

		error = bma150_set_low_g_interrupt(bma150,
					cfg->lg_int, cfg->lg_hyst,
					cfg->lg_dur, cfg->lg_thres);
		if (error)
			return error;
	}

	return bma150_set_mode(bma150, BMA150_MODE_SLEEP);
}