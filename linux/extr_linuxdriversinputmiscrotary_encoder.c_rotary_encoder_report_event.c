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
struct rotary_encoder {scalar_t__ dir; unsigned int pos; unsigned int steps; int /*<<< orphan*/  input; int /*<<< orphan*/  axis; scalar_t__ rollover; scalar_t__ relative_axis; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rotary_encoder_report_event(struct rotary_encoder *encoder)
{
	if (encoder->relative_axis) {
		input_report_rel(encoder->input,
				 encoder->axis, encoder->dir);
	} else {
		unsigned int pos = encoder->pos;

		if (encoder->dir < 0) {
			/* turning counter-clockwise */
			if (encoder->rollover)
				pos += encoder->steps;
			if (pos)
				pos--;
		} else {
			/* turning clockwise */
			if (encoder->rollover || pos < encoder->steps)
				pos++;
		}

		if (encoder->rollover)
			pos %= encoder->steps;

		encoder->pos = pos;
		input_report_abs(encoder->input, encoder->axis, encoder->pos);
	}

	input_sync(encoder->input);
}