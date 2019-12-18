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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ is_power_of_2 (scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ roundup_pow_of_two (scalar_t__) ; 

__attribute__((used)) static u16
ath5k_cw_validate(u16 cw_req)
{
	cw_req = min(cw_req, (u16)1023);

	/* Check if cw_req + 1 a power of 2 */
	if (is_power_of_2(cw_req + 1))
		return cw_req;

	/* Check if cw_req is a power of 2 */
	if (is_power_of_2(cw_req))
		return cw_req - 1;

	/* If none of the above is correct
	 * find the closest power of 2 */
	cw_req = (u16) roundup_pow_of_two(cw_req) - 1;

	return cw_req;
}