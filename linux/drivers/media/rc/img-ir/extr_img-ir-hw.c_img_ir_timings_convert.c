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
struct img_ir_timings {int /*<<< orphan*/  ft; int /*<<< orphan*/  s11; int /*<<< orphan*/  s10; int /*<<< orphan*/  s01; int /*<<< orphan*/  s00; int /*<<< orphan*/  ldr; } ;
struct img_ir_timing_regvals {int /*<<< orphan*/  ft; void* s11; void* s10; void* s01; void* s00; void* ldr; } ;

/* Variables and functions */
 int /*<<< orphan*/  img_ir_free_timing (int /*<<< orphan*/ *,unsigned int) ; 
 void* img_ir_symbol_timing (int /*<<< orphan*/ *,unsigned int,unsigned int,int,int) ; 

__attribute__((used)) static void img_ir_timings_convert(struct img_ir_timing_regvals *regs,
				   const struct img_ir_timings *timings,
				   unsigned int tolerance,
				   unsigned int clock_hz)
{
	/* leader symbol timings are divided by 16 */
	regs->ldr = img_ir_symbol_timing(&timings->ldr, tolerance, clock_hz,
			4, 4);
	/* other symbol timings, pd fields only are divided by 2 */
	regs->s00 = img_ir_symbol_timing(&timings->s00, tolerance, clock_hz,
			1, 0);
	regs->s01 = img_ir_symbol_timing(&timings->s01, tolerance, clock_hz,
			1, 0);
	regs->s10 = img_ir_symbol_timing(&timings->s10, tolerance, clock_hz,
			1, 0);
	regs->s11 = img_ir_symbol_timing(&timings->s11, tolerance, clock_hz,
			1, 0);
	regs->ft = img_ir_free_timing(&timings->ft, clock_hz);
}