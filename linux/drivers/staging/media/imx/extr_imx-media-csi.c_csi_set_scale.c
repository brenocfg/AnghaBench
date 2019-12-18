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
 int ERANGE ; 
 int V4L2_SEL_FLAG_GE ; 
 int V4L2_SEL_FLAG_LE ; 

__attribute__((used)) static int csi_set_scale(u32 *compose, u32 crop, u32 flags)
{
	if ((flags & (V4L2_SEL_FLAG_LE | V4L2_SEL_FLAG_GE)) ==
		     (V4L2_SEL_FLAG_LE | V4L2_SEL_FLAG_GE) &&
	    *compose != crop && *compose != crop / 2)
		return -ERANGE;

	if (*compose <= crop / 2 ||
	    (*compose < crop * 3 / 4 && !(flags & V4L2_SEL_FLAG_GE)) ||
	    (*compose < crop && (flags & V4L2_SEL_FLAG_LE)))
		*compose = crop / 2;
	else
		*compose = crop;

	return 0;
}