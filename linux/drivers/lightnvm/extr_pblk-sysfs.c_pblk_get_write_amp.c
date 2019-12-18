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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int div64_u64 (int,int) ; 
 int div_u64_rem (int,int,int /*<<< orphan*/ *) ; 
 int snprintf (char*,scalar_t__,char*,...) ; 

__attribute__((used)) static ssize_t pblk_get_write_amp(u64 user, u64 gc, u64 pad,
				  char *page)
{
	int sz;

	sz = snprintf(page, PAGE_SIZE,
			"user:%lld gc:%lld pad:%lld WA:",
			user, gc, pad);

	if (!user) {
		sz += snprintf(page + sz, PAGE_SIZE - sz, "NaN\n");
	} else {
		u64 wa_int;
		u32 wa_frac;

		wa_int = (user + gc + pad) * 100000;
		wa_int = div64_u64(wa_int, user);
		wa_int = div_u64_rem(wa_int, 100000, &wa_frac);

		sz += snprintf(page + sz, PAGE_SIZE - sz, "%llu.%05u\n",
							wa_int, wa_frac);
	}

	return sz;
}