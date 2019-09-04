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
struct img_ir_reg_timings {int /*<<< orphan*/  rtimings; int /*<<< orphan*/  timings; int /*<<< orphan*/  ctrl; } ;
struct img_ir_decoder {int /*<<< orphan*/  tolerance; int /*<<< orphan*/  rtimings; scalar_t__ repeat; int /*<<< orphan*/  timings; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  img_ir_control (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  img_ir_timings_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void img_ir_decoder_convert(const struct img_ir_decoder *decoder,
				   struct img_ir_reg_timings *reg_timings,
				   unsigned int clock_hz)
{
	/* calculate control value */
	reg_timings->ctrl = img_ir_control(&decoder->control);

	/* fill in implicit fields and calculate register values */
	img_ir_timings_convert(&reg_timings->timings, &decoder->timings,
			       decoder->tolerance, clock_hz);

	/* do the same for repeat timings if applicable */
	if (decoder->repeat)
		img_ir_timings_convert(&reg_timings->rtimings,
				       &decoder->rtimings, decoder->tolerance,
				       clock_hz);
}