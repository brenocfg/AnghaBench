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
typedef  enum lp8727_die_temp { ____Placeholder_lp8727_die_temp } lp8727_die_temp ;

/* Variables and functions */
#define  LP8788_TEMP_115C 130 
#define  LP8788_TEMP_135C 129 
#define  LP8788_TEMP_95C 128 

__attribute__((used)) static bool lp8727_is_high_temperature(enum lp8727_die_temp temp)
{
	switch (temp) {
	case LP8788_TEMP_95C:
	case LP8788_TEMP_115C:
	case LP8788_TEMP_135C:
		return true;
	default:
		return false;
	}
}