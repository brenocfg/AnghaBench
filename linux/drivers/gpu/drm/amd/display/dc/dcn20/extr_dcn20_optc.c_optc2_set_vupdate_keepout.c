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
struct vupdate_keepout_params {int /*<<< orphan*/  enable; int /*<<< orphan*/  end_offset; int /*<<< orphan*/  start_offset; } ;
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_END_OFFSET ; 
 int /*<<< orphan*/  MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_START_OFFSET ; 
 int /*<<< orphan*/  OTG_MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_EN ; 
 int /*<<< orphan*/  OTG_VUPDATE_KEEPOUT ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void optc2_set_vupdate_keepout(struct timing_generator *optc,
		   const struct vupdate_keepout_params *params)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_3(OTG_VUPDATE_KEEPOUT, 0,
		MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_START_OFFSET, params->start_offset,
		MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_END_OFFSET, params->end_offset,
		OTG_MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_EN, params->enable);
}