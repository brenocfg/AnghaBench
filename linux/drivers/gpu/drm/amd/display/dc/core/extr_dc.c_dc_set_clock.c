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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int (* set_clock ) (struct dc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dc {TYPE_1__ hwss; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
typedef  enum dc_clock_type { ____Placeholder_dc_clock_type } dc_clock_type ;

/* Variables and functions */
 int DC_ERROR_UNEXPECTED ; 
 int stub1 (struct dc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum dc_status dc_set_clock(struct dc *dc, enum dc_clock_type clock_type, uint32_t clk_khz, uint32_t stepping)
{
	if (dc->hwss.set_clock)
		return dc->hwss.set_clock(dc, clock_type, clk_khz, stepping);
	return DC_ERROR_UNEXPECTED;
}