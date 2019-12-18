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

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int fls (int) ; 

int denali_calc_ecc_bytes(int step_size, int strength)
{
	/* BCH code.  Denali requires ecc.bytes to be multiple of 2 */
	return DIV_ROUND_UP(strength * fls(step_size * 8), 16) * 2;
}