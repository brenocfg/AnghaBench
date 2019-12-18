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
typedef  scalar_t__ u32 ;
struct mcam_format_struct {scalar_t__ pixelformat; } ;

/* Variables and functions */
 unsigned int N_MCAM_FMTS ; 
 struct mcam_format_struct* mcam_formats ; 

__attribute__((used)) static struct mcam_format_struct *mcam_find_format(u32 pixelformat)
{
	unsigned i;

	for (i = 0; i < N_MCAM_FMTS; i++)
		if (mcam_formats[i].pixelformat == pixelformat)
			return mcam_formats + i;
	/* Not found? Then return the first format. */
	return mcam_formats;
}