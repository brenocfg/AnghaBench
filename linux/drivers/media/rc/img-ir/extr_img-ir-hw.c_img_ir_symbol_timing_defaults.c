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
 int /*<<< orphan*/  img_ir_timing_defaults (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void img_ir_symbol_timing_defaults(struct img_ir_symbol_timing *timing,
					  struct img_ir_symbol_timing *defaults)
{
	img_ir_timing_defaults(&timing->pulse, &defaults->pulse);
	img_ir_timing_defaults(&timing->space, &defaults->space);
}