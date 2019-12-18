#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uvesafb_par {int mtrr_handle; } ;
struct TYPE_2__ {int smem_start; int smem_len; } ;
struct fb_info {TYPE_1__ fix; struct uvesafb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int arch_phys_wc_add (int,int) ; 
 scalar_t__ mtrr ; 
 int roundup_pow_of_two (int) ; 

__attribute__((used)) static void uvesafb_init_mtrr(struct fb_info *info)
{
	struct uvesafb_par *par = info->par;

	if (mtrr && !(info->fix.smem_start & (PAGE_SIZE - 1))) {
		int temp_size = info->fix.smem_len;

		int rc;

		/* Find the largest power-of-two */
		temp_size = roundup_pow_of_two(temp_size);

		/* Try and find a power of two to add */
		do {
			rc = arch_phys_wc_add(info->fix.smem_start, temp_size);
			temp_size >>= 1;
		} while (temp_size >= PAGE_SIZE && rc == -EINVAL);

		if (rc >= 0)
			par->mtrr_handle = rc;
	}
}