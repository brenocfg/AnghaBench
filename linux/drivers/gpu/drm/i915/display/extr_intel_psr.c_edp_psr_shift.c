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
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int EDP_PSR_TRANSCODER_A_SHIFT ; 
 int EDP_PSR_TRANSCODER_B_SHIFT ; 
 int EDP_PSR_TRANSCODER_C_SHIFT ; 
 int EDP_PSR_TRANSCODER_EDP_SHIFT ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  TRANSCODER_A 131 
#define  TRANSCODER_B 130 
#define  TRANSCODER_C 129 
#define  TRANSCODER_EDP 128 

__attribute__((used)) static int edp_psr_shift(enum transcoder cpu_transcoder)
{
	switch (cpu_transcoder) {
	case TRANSCODER_A:
		return EDP_PSR_TRANSCODER_A_SHIFT;
	case TRANSCODER_B:
		return EDP_PSR_TRANSCODER_B_SHIFT;
	case TRANSCODER_C:
		return EDP_PSR_TRANSCODER_C_SHIFT;
	default:
		MISSING_CASE(cpu_transcoder);
		/* fallthrough */
	case TRANSCODER_EDP:
		return EDP_PSR_TRANSCODER_EDP_SHIFT;
	}
}