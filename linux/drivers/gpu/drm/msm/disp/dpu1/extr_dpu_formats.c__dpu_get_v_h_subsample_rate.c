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
typedef  int uint32_t ;
typedef  enum dpu_chroma_samp_type { ____Placeholder_dpu_chroma_samp_type } dpu_chroma_samp_type ;

/* Variables and functions */
#define  DPU_CHROMA_420 130 
#define  DPU_CHROMA_H1V2 129 
#define  DPU_CHROMA_H2V1 128 

__attribute__((used)) static void _dpu_get_v_h_subsample_rate(
	enum dpu_chroma_samp_type chroma_sample,
	uint32_t *v_sample,
	uint32_t *h_sample)
{
	if (!v_sample || !h_sample)
		return;

	switch (chroma_sample) {
	case DPU_CHROMA_H2V1:
		*v_sample = 1;
		*h_sample = 2;
		break;
	case DPU_CHROMA_H1V2:
		*v_sample = 2;
		*h_sample = 1;
		break;
	case DPU_CHROMA_420:
		*v_sample = 2;
		*h_sample = 2;
		break;
	default:
		*v_sample = 1;
		*h_sample = 1;
		break;
	}
}