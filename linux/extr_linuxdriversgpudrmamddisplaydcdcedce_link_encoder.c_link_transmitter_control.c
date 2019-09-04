#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ctx; } ;
struct dce110_link_encoder {TYPE_2__ base; } ;
struct dc_bios {TYPE_3__* funcs; } ;
struct bp_transmitter_control {int dummy; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_6__ {int (* transmitter_control ) (struct dc_bios*,struct bp_transmitter_control*) ;} ;
struct TYPE_4__ {struct dc_bios* dc_bios; } ;

/* Variables and functions */
 int stub1 (struct dc_bios*,struct bp_transmitter_control*) ; 

__attribute__((used)) static enum bp_result link_transmitter_control(
	struct dce110_link_encoder *enc110,
	struct bp_transmitter_control *cntl)
{
	enum bp_result result;
	struct dc_bios *bp = enc110->base.ctx->dc_bios;

	result = bp->funcs->transmitter_control(bp, cntl);

	return result;
}