#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  Doorbell; int /*<<< orphan*/  IntStatus; } ;
typedef  TYPE_2__ MPT_ADAPTER ;

/* Variables and functions */
 int CHIPREG_READ32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHIPREG_WRITE32 (int /*<<< orphan*/ *,int) ; 
 int MPI_DOORBELL_ACTIVE ; 
 int MPI_DOORBELL_FUNCTION_SHIFT ; 
 int MPI_FUNCTION_HOST_PAGEBUF_ACCESS_CONTROL ; 
 int WaitForDoorbellAck (TYPE_2__*,int,int) ; 

__attribute__((used)) static int
mpt_host_page_access_control(MPT_ADAPTER *ioc, u8 access_control_value, int sleepFlag)
{
	int	 r = 0;

	/* return if in use */
	if (CHIPREG_READ32(&ioc->chip->Doorbell)
	    & MPI_DOORBELL_ACTIVE)
	    return -1;

	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	CHIPREG_WRITE32(&ioc->chip->Doorbell,
		((MPI_FUNCTION_HOST_PAGEBUF_ACCESS_CONTROL
		 <<MPI_DOORBELL_FUNCTION_SHIFT) |
		 (access_control_value<<12)));

	/* Wait for IOC to clear Doorbell Status bit */
	if ((r = WaitForDoorbellAck(ioc, 5, sleepFlag)) < 0) {
		return -2;
	}else
		return 0;
}