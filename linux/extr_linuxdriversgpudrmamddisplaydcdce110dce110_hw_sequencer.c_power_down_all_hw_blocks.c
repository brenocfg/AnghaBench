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
struct dc {TYPE_2__* fbc_compressor; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_fbc ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  power_down_clock_sources (struct dc*) ; 
 int /*<<< orphan*/  power_down_controllers (struct dc*) ; 
 int /*<<< orphan*/  power_down_encoders (struct dc*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void power_down_all_hw_blocks(struct dc *dc)
{
	power_down_encoders(dc);

	power_down_controllers(dc);

	power_down_clock_sources(dc);

	if (dc->fbc_compressor)
		dc->fbc_compressor->funcs->disable_fbc(dc->fbc_compressor);
}