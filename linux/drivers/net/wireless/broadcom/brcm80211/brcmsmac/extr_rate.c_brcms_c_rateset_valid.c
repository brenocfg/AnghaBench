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
typedef  size_t uint ;
struct brcms_c_rateset {size_t count; int* rates; } ;

/* Variables and functions */
 int BRCMS_RATE_FLAG ; 

__attribute__((used)) static bool brcms_c_rateset_valid(struct brcms_c_rateset *rs, bool check_brate)
{
	uint idx;

	if (!rs->count)
		return false;

	if (!check_brate)
		return true;

	/* error if no basic rates */
	for (idx = 0; idx < rs->count; idx++) {
		if (rs->rates[idx] & BRCMS_RATE_FLAG)
			return true;
	}
	return false;
}