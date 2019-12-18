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
struct rbsp {int /*<<< orphan*/  error; } ;
struct nal_h264_hrd_parameters {unsigned int cpb_cnt_minus1; unsigned int* bit_rate_value_minus1; unsigned int* cpb_size_value_minus1; int /*<<< orphan*/  time_offset_length; int /*<<< orphan*/  dpb_output_delay_length_minus1; int /*<<< orphan*/  cpb_removal_delay_length_minus1; int /*<<< orphan*/  initial_cpb_removal_delay_length_minus1; int /*<<< orphan*/ * cbr_flag; int /*<<< orphan*/  cpb_size_scale; int /*<<< orphan*/  bit_rate_scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  rbsp_bit (struct rbsp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbsp_bits (struct rbsp*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbsp_uev (struct rbsp*,unsigned int*) ; 

__attribute__((used)) static void nal_h264_rbsp_hrd_parameters(struct rbsp *rbsp,
					 struct nal_h264_hrd_parameters *hrd)
{
	unsigned int i;

	if (!hrd) {
		rbsp->error = -EINVAL;
		return;
	}

	rbsp_uev(rbsp, &hrd->cpb_cnt_minus1);
	rbsp_bits(rbsp, 4, &hrd->bit_rate_scale);
	rbsp_bits(rbsp, 4, &hrd->cpb_size_scale);

	for (i = 0; i <= hrd->cpb_cnt_minus1; i++) {
		rbsp_uev(rbsp, &hrd->bit_rate_value_minus1[i]);
		rbsp_uev(rbsp, &hrd->cpb_size_value_minus1[i]);
		rbsp_bit(rbsp, &hrd->cbr_flag[i]);
	}

	rbsp_bits(rbsp, 5, &hrd->initial_cpb_removal_delay_length_minus1);
	rbsp_bits(rbsp, 5, &hrd->cpb_removal_delay_length_minus1);
	rbsp_bits(rbsp, 5, &hrd->dpb_output_delay_length_minus1);
	rbsp_bits(rbsp, 5, &hrd->time_offset_length);
}