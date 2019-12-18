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
struct TYPE_2__ {scalar_t__ ft_min; } ;
struct img_ir_timings {TYPE_1__ ft; int /*<<< orphan*/  s11; int /*<<< orphan*/  s10; int /*<<< orphan*/  s01; int /*<<< orphan*/  s00; int /*<<< orphan*/  ldr; } ;

/* Variables and functions */
 int /*<<< orphan*/  img_ir_symbol_timing_defaults (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void img_ir_timings_defaults(struct img_ir_timings *timings,
				    struct img_ir_timings *defaults)
{
	img_ir_symbol_timing_defaults(&timings->ldr, &defaults->ldr);
	img_ir_symbol_timing_defaults(&timings->s00, &defaults->s00);
	img_ir_symbol_timing_defaults(&timings->s01, &defaults->s01);
	img_ir_symbol_timing_defaults(&timings->s10, &defaults->s10);
	img_ir_symbol_timing_defaults(&timings->s11, &defaults->s11);
	if (!timings->ft.ft_min)
		timings->ft.ft_min = defaults->ft.ft_min;
}