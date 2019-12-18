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
typedef  enum i2c_status { ____Placeholder_i2c_status } i2c_status ;

/* Variables and functions */
#define  DONE_STOP 129 
#define  IDLE 128 

__attribute__((used)) static inline int i2c_is_idle(enum i2c_status status)
{
	switch (status) {
	case IDLE:
	case DONE_STOP:
		return true;
	default:
		return false;
	}
}