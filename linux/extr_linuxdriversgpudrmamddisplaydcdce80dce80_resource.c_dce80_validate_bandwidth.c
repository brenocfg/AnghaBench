#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dispclk_khz; int yclk_khz; } ;
struct TYPE_4__ {TYPE_1__ dce; } ;
struct dc_state {TYPE_2__ bw; } ;
struct dc {int dummy; } ;

/* Variables and functions */
 int MEMORY_TYPE_MULTIPLIER ; 

bool dce80_validate_bandwidth(
	struct dc *dc,
	struct dc_state *context)
{
	/* TODO implement when needed but for now hardcode max value*/
	context->bw.dce.dispclk_khz = 681000;
	context->bw.dce.yclk_khz = 250000 * MEMORY_TYPE_MULTIPLIER;

	return true;
}