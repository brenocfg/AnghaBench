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
struct dc_bios {TYPE_1__* funcs; } ;
struct bp_transmitter_control {int dummy; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_2__ {int (* transmitter_control ) (struct dc_bios*,struct bp_transmitter_control*) ;} ;

/* Variables and functions */
 int stub1 (struct dc_bios*,struct bp_transmitter_control*) ; 

__attribute__((used)) static enum bp_result link_transmitter_control(
		struct dc_bios *bios,
	struct bp_transmitter_control *cntl)
{
	enum bp_result result;

	result = bios->funcs->transmitter_control(bios, cntl);

	return result;
}