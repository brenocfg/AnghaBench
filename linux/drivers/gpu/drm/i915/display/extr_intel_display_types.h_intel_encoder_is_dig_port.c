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
struct intel_encoder {int type; } ;

/* Variables and functions */
#define  INTEL_OUTPUT_DDI 131 
#define  INTEL_OUTPUT_DP 130 
#define  INTEL_OUTPUT_EDP 129 
#define  INTEL_OUTPUT_HDMI 128 

__attribute__((used)) static inline bool intel_encoder_is_dig_port(struct intel_encoder *encoder)
{
	switch (encoder->type) {
	case INTEL_OUTPUT_DDI:
	case INTEL_OUTPUT_DP:
	case INTEL_OUTPUT_EDP:
	case INTEL_OUTPUT_HDMI:
		return true;
	default:
		return false;
	}
}