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
typedef  enum fe_stv0900_rolloff { ____Placeholder_fe_stv0900_rolloff } fe_stv0900_rolloff ;

/* Variables and functions */
#define  STV0900_20 130 
#define  STV0900_25 129 
#define  STV0900_35 128 

__attribute__((used)) static u32 stv0900_carrier_width(u32 srate, enum fe_stv0900_rolloff ro)
{
	u32 rolloff;

	switch (ro) {
	case STV0900_20:
		rolloff = 20;
		break;
	case STV0900_25:
		rolloff = 25;
		break;
	case STV0900_35:
	default:
		rolloff = 35;
		break;
	}

	return srate  + (srate * rolloff) / 100;
}