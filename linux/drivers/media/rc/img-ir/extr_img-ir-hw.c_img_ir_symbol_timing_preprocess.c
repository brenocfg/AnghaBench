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
struct img_ir_symbol_timing {int /*<<< orphan*/  space; int /*<<< orphan*/  pulse; } ;

/* Variables and functions */
 int /*<<< orphan*/  img_ir_timing_preprocess (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void img_ir_symbol_timing_preprocess(struct img_ir_symbol_timing *timing,
					    unsigned int unit)
{
	img_ir_timing_preprocess(&timing->pulse, unit);
	img_ir_timing_preprocess(&timing->space, unit);
}