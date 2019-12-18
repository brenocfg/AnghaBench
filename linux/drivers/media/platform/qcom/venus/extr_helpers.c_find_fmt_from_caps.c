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
typedef  scalar_t__ u32 ;
struct venus_caps {unsigned int num_fmts; TYPE_1__* fmts; } ;
struct TYPE_2__ {scalar_t__ buftype; scalar_t__ fmt; } ;

/* Variables and functions */

__attribute__((used)) static bool find_fmt_from_caps(struct venus_caps *caps, u32 buftype, u32 fmt)
{
	unsigned int i;

	for (i = 0; i < caps->num_fmts; i++) {
		if (caps->fmts[i].buftype == buftype &&
		    caps->fmts[i].fmt == fmt)
			return true;
	}

	return false;
}