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
#define  BUSY 130 
#define  TO_ARB 129 
#define  TO_SCL 128 

__attribute__((used)) static inline int i2c_is_busy(enum i2c_status status)
{
	switch (status) {
	case BUSY:
	case TO_SCL:
	case TO_ARB:
		return true;
	default:
		return false;
	}
}