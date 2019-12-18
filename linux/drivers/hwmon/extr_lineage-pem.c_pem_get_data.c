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
#define  PEM_DATA_CURRENT 132 
#define  PEM_DATA_TEMP 131 
#define  PEM_DATA_TEMP_CRIT 130 
#define  PEM_DATA_TEMP_MAX 129 
#define  PEM_DATA_VOUT_LSB 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static long pem_get_data(u8 *data, int len, int index)
{
	long val;

	switch (index) {
	case PEM_DATA_VOUT_LSB:
		val = (data[index] + (data[index+1] << 8)) * 5 / 2;
		break;
	case PEM_DATA_CURRENT:
		val = data[index] * 200;
		break;
	case PEM_DATA_TEMP:
		val = data[index] * 1000;
		break;
	case PEM_DATA_TEMP_MAX:
		val = 97 * 1000;	/* 97 degrees C per datasheet */
		break;
	case PEM_DATA_TEMP_CRIT:
		val = 107 * 1000;	/* 107 degrees C per datasheet */
		break;
	default:
		WARN_ON_ONCE(1);
		val = 0;
	}
	return val;
}