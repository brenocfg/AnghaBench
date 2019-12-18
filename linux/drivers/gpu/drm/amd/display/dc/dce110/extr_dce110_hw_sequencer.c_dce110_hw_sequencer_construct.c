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
struct dc {int /*<<< orphan*/  hwss; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce110_funcs ; 

void dce110_hw_sequencer_construct(struct dc *dc)
{
	dc->hwss = dce110_funcs;
}