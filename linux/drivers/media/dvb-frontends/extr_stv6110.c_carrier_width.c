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
typedef  int u32 ;
typedef  enum fe_rolloff { ____Placeholder_fe_rolloff } fe_rolloff ;

/* Variables and functions */
#define  ROLLOFF_20 129 
#define  ROLLOFF_25 128 

__attribute__((used)) static u32 carrier_width(u32 symbol_rate, enum fe_rolloff rolloff)
{
	u32 rlf;

	switch (rolloff) {
	case ROLLOFF_20:
		rlf = 20;
		break;
	case ROLLOFF_25:
		rlf = 25;
		break;
	default:
		rlf = 35;
		break;
	}

	return symbol_rate  + ((symbol_rate * rlf) / 100);
}