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
struct uni_name_t {int name_len; } ;
typedef  int s32 ;

/* Variables and functions */

s32 fat_calc_num_entries(struct uni_name_t *p_uniname)
{
	s32 len;

	len = p_uniname->name_len;
	if (len == 0)
		return 0;

	/* 1 dos name entry + extended entries */
	return (len - 1) / 13 + 2;
}