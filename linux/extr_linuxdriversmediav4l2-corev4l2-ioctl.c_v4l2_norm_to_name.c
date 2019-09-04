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
typedef  scalar_t__ v4l2_std_id ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ std; char const* descr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* standards ; 

const char *v4l2_norm_to_name(v4l2_std_id id)
{
	u32 myid = id;
	int i;

	/* HACK: ppc32 architecture doesn't have __ucmpdi2 function to handle
	   64 bit comparations. So, on that architecture, with some gcc
	   variants, compilation fails. Currently, the max value is 30bit wide.
	 */
	BUG_ON(myid != id);

	for (i = 0; standards[i].std; i++)
		if (myid == standards[i].std)
			break;
	return standards[i].descr;
}