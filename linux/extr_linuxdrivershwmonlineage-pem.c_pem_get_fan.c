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
#define  PEM_FAN_FAN1 130 
#define  PEM_FAN_FAN2 129 
#define  PEM_FAN_FAN3 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static long pem_get_fan(u8 *data, int len, int index)
{
	long val;

	switch (index) {
	case PEM_FAN_FAN1:
	case PEM_FAN_FAN2:
	case PEM_FAN_FAN3:
		val = data[index] * 100;
		break;
	default:
		WARN_ON_ONCE(1);
		val = 0;
	}
	return val;
}