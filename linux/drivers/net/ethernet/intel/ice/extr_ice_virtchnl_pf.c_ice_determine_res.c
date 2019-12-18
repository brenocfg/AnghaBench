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
typedef  int u16 ;
struct ice_pf {int num_alloc_vfs; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static int
ice_determine_res(struct ice_pf *pf, u16 avail_res, u16 max_res, u16 min_res)
{
	bool checked_min_res = false;
	int res;

	/* start by checking if PF can assign max number of resources for
	 * all num_alloc_vfs.
	 * if yes, return number per VF
	 * If no, divide by 2 and roundup, check again
	 * repeat the loop till we reach a point where even minimum resources
	 * are not available, in that case return 0
	 */
	res = max_res;
	while ((res >= min_res) && !checked_min_res) {
		int num_all_res;

		num_all_res = pf->num_alloc_vfs * res;
		if (num_all_res <= avail_res)
			return res;

		if (res == min_res)
			checked_min_res = true;

		res = DIV_ROUND_UP(res, 2);
	}
	return 0;
}