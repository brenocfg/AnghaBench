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

/* Variables and functions */
 int TW_STATUS_EXPECTED_BITS ; 
 int TW_STATUS_UNEXPECTED_BITS ; 

__attribute__((used)) static int twa_check_bits(u32 status_reg_value)
{
	int retval = 1;

	if ((status_reg_value & TW_STATUS_EXPECTED_BITS) != TW_STATUS_EXPECTED_BITS)
		goto out;
	if ((status_reg_value & TW_STATUS_UNEXPECTED_BITS) != 0)
		goto out;

	retval = 0;
out:
	return retval;
}