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
typedef  int u8 ;

/* Variables and functions */
#define  TEMP_TYPE_LOCAL_DIODE 130 
 int TEMP_TYPE_MASK ; 
#define  TEMP_TYPE_REMOTE_DIODE 129 
#define  TEMP_TYPE_THERMISTOR 128 

__attribute__((used)) static inline unsigned int temp_type_from_reg(u8 reg)
{
	switch (reg & TEMP_TYPE_MASK) {
	case TEMP_TYPE_THERMISTOR:
		return 4;
	case TEMP_TYPE_REMOTE_DIODE:
	case TEMP_TYPE_LOCAL_DIODE:
		return 3;
	default:
		return 0;
	}
}