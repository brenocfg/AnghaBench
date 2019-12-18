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
struct imgu_css_scaler_info {int phase_step; int pad_left; int pad_right; int phase_init; unsigned int crop_left; unsigned int crop_top; scalar_t__ exp_shift; } ;
typedef  int s8 ;
typedef  int s64 ;

/* Variables and functions */
 int IMGU_SCALER_COEFF_BITS ; 
 int IMGU_SCALER_FILTER_TAPS ; 
 scalar_t__ IMGU_SCALER_MAX_EXPONENT_SHIFT ; 
 int IMGU_SCALER_PHASES ; 
 int IMGU_SCALER_PHASE_COUNTER_PREC_REF ; 
 int div64_long (int,unsigned int) ; 
 int imgu_css_scaler_get_exp (unsigned int,unsigned int) ; 

__attribute__((used)) static void
imgu_css_scaler_setup_lut(unsigned int taps, unsigned int input_width,
			  unsigned int output_width, int phase_step_correction,
			  const int *coeffs, unsigned int coeffs_size,
			  s8 coeff_lut[], struct imgu_css_scaler_info *info)
{
	int tap, phase, phase_sum_left, phase_sum_right;
	int exponent = imgu_css_scaler_get_exp(output_width, input_width);
	int mantissa = (1 << exponent) * output_width;
	unsigned int phase_step;

	if (input_width == output_width) {
		for (phase = 0; phase < IMGU_SCALER_PHASES; phase++) {
			for (tap = 0; tap < taps; tap++) {
				coeff_lut[phase * IMGU_SCALER_FILTER_TAPS + tap]
					= 0;
			}
		}

		info->phase_step = IMGU_SCALER_PHASES *
			(1 << IMGU_SCALER_PHASE_COUNTER_PREC_REF);
		info->exp_shift = 0;
		info->pad_left = 0;
		info->pad_right = 0;
		info->phase_init = 0;
		info->crop_left = 0;
		info->crop_top = 0;
		return;
	}

	for (phase = 0; phase < IMGU_SCALER_PHASES; phase++) {
		for (tap = 0; tap < taps; tap++) {
			/* flip table to for convolution reverse indexing */
			s64 coeff = coeffs[coeffs_size -
				((tap * (coeffs_size / taps)) + phase) - 1];
			coeff *= mantissa;
			coeff = div64_long(coeff, input_width);

			/* Add +"0.5" */
			coeff += 1 << (IMGU_SCALER_COEFF_BITS - 1);
			coeff >>= IMGU_SCALER_COEFF_BITS;

			coeff_lut[phase * IMGU_SCALER_FILTER_TAPS + tap] =
				coeff;
		}
	}

	phase_step = IMGU_SCALER_PHASES *
			(1 << IMGU_SCALER_PHASE_COUNTER_PREC_REF) *
			output_width / input_width;
	phase_step += phase_step_correction;
	phase_sum_left = (taps / 2 * IMGU_SCALER_PHASES *
			(1 << IMGU_SCALER_PHASE_COUNTER_PREC_REF)) -
			(1 << (IMGU_SCALER_PHASE_COUNTER_PREC_REF - 1));
	phase_sum_right = (taps / 2 * IMGU_SCALER_PHASES *
			(1 << IMGU_SCALER_PHASE_COUNTER_PREC_REF)) +
			(1 << (IMGU_SCALER_PHASE_COUNTER_PREC_REF - 1));

	info->exp_shift = IMGU_SCALER_MAX_EXPONENT_SHIFT - exponent;
	info->pad_left = (phase_sum_left % phase_step == 0) ?
		phase_sum_left / phase_step - 1 : phase_sum_left / phase_step;
	info->pad_right = (phase_sum_right % phase_step == 0) ?
		phase_sum_right / phase_step - 1 : phase_sum_right / phase_step;
	info->phase_init = phase_sum_left - phase_step * info->pad_left;
	info->phase_step = phase_step;
	info->crop_left = taps - 1;
	info->crop_top = taps - 1;
}