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
typedef  int u8 ;
struct TYPE_2__ {int IOCCapabilities; } ;
struct MPT3SAS_ADAPTER {TYPE_1__ facts; } ;

/* Variables and functions */
#define  MPI2_DIAG_BUF_TYPE_EXTENDED 130 
#define  MPI2_DIAG_BUF_TYPE_SNAPSHOT 129 
#define  MPI2_DIAG_BUF_TYPE_TRACE 128 
 int MPI2_IOCFACTS_CAPABILITY_DIAG_TRACE_BUFFER ; 
 int MPI2_IOCFACTS_CAPABILITY_EXTENDED_BUFFER ; 
 int MPI2_IOCFACTS_CAPABILITY_SNAPSHOT_BUFFER ; 

__attribute__((used)) static u8
_ctl_diag_capability(struct MPT3SAS_ADAPTER *ioc, u8 buffer_type)
{
	u8 rc = 0;

	switch (buffer_type) {
	case MPI2_DIAG_BUF_TYPE_TRACE:
		if (ioc->facts.IOCCapabilities &
		    MPI2_IOCFACTS_CAPABILITY_DIAG_TRACE_BUFFER)
			rc = 1;
		break;
	case MPI2_DIAG_BUF_TYPE_SNAPSHOT:
		if (ioc->facts.IOCCapabilities &
		    MPI2_IOCFACTS_CAPABILITY_SNAPSHOT_BUFFER)
			rc = 1;
		break;
	case MPI2_DIAG_BUF_TYPE_EXTENDED:
		if (ioc->facts.IOCCapabilities &
		    MPI2_IOCFACTS_CAPABILITY_EXTENDED_BUFFER)
			rc = 1;
	}

	return rc;
}