#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int last_state; TYPE_1__* chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  Doorbell; } ;
typedef  TYPE_2__ MPT_ADAPTER ;

/* Variables and functions */
 int CHIPREG_READ32 (int /*<<< orphan*/ *) ; 
 int MPI_IOC_STATE_MASK ; 

u32
mpt_GetIocState(MPT_ADAPTER *ioc, int cooked)
{
	u32 s, sc;

	/*  Get!  */
	s = CHIPREG_READ32(&ioc->chip->Doorbell);
	sc = s & MPI_IOC_STATE_MASK;

	/*  Save!  */
	ioc->last_state = sc;

	return cooked ? sc : s;
}