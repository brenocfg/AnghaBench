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
struct TYPE_2__ {unsigned int ft_min; } ;
struct img_ir_timings {TYPE_1__ ft; int /*<<< orphan*/  s11; int /*<<< orphan*/  s10; int /*<<< orphan*/  s01; int /*<<< orphan*/  s00; int /*<<< orphan*/  ldr; } ;

/* Variables and functions */
 int /*<<< orphan*/  img_ir_symbol_timing_preprocess (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void img_ir_timings_preprocess(struct img_ir_timings *timings,
				      unsigned int unit)
{
	img_ir_symbol_timing_preprocess(&timings->ldr, unit);
	img_ir_symbol_timing_preprocess(&timings->s00, unit);
	img_ir_symbol_timing_preprocess(&timings->s01, unit);
	img_ir_symbol_timing_preprocess(&timings->s10, unit);
	img_ir_symbol_timing_preprocess(&timings->s11, unit);
	/* default s10 and s11 to s00 and s01 if no leader */
	if (unit)
		/* multiply by unit and convert to microseconds (round up) */
		timings->ft.ft_min = (timings->ft.ft_min*unit + 999)/1000;
}