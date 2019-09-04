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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum fe_code_rate { ____Placeholder_fe_code_rate } fe_code_rate ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_RATE_1_2 ; 
 int /*<<< orphan*/  CODE_RATE_2_3 ; 
 int /*<<< orphan*/  CODE_RATE_3_4 ; 
 int /*<<< orphan*/  CODE_RATE_5_6 ; 
 int /*<<< orphan*/  CODE_RATE_7_8 ; 
 int /*<<< orphan*/  CODE_RATE_UNKNOWN ; 
#define  FEC_1_2 132 
#define  FEC_2_3 131 
#define  FEC_3_4 130 
#define  FEC_5_6 129 
#define  FEC_7_8 128 

__attribute__((used)) static uint8_t as102_fe_get_code_rate(enum fe_code_rate arg)
{
	uint8_t c;

	switch (arg) {
	case FEC_1_2:
		c = CODE_RATE_1_2;
		break;
	case FEC_2_3:
		c = CODE_RATE_2_3;
		break;
	case FEC_3_4:
		c = CODE_RATE_3_4;
		break;
	case FEC_5_6:
		c = CODE_RATE_5_6;
		break;
	case FEC_7_8:
		c = CODE_RATE_7_8;
		break;
	default:
		c = CODE_RATE_UNKNOWN;
		break;
	}

	return c;
}