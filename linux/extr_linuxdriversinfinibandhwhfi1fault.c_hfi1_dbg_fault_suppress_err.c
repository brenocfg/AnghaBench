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
struct hfi1_ibdev {TYPE_1__* fault; } ;
struct TYPE_2__ {int suppress_err; } ;

/* Variables and functions */

bool hfi1_dbg_fault_suppress_err(struct hfi1_ibdev *ibd)
{
	if (ibd->fault)
		return ibd->fault->suppress_err;
	return false;
}