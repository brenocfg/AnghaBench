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
struct dc_clock_config {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_clock ) (struct dc*,int,struct dc_clock_config*) ;} ;
struct dc {TYPE_1__ hwss; } ;
typedef  enum dc_clock_type { ____Placeholder_dc_clock_type } dc_clock_type ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dc*,int,struct dc_clock_config*) ; 

void dc_get_clock(struct dc *dc, enum dc_clock_type clock_type, struct dc_clock_config *clock_cfg)
{
	if (dc->hwss.get_clock)
		dc->hwss.get_clock(dc, clock_type, clock_cfg);
}