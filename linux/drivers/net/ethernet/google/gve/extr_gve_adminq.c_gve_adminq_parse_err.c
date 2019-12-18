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
struct device {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int ETIME ; 
#define  GVE_ADMINQ_COMMAND_ERROR_ABORTED 145 
#define  GVE_ADMINQ_COMMAND_ERROR_ALREADY_EXISTS 144 
#define  GVE_ADMINQ_COMMAND_ERROR_CANCELLED 143 
#define  GVE_ADMINQ_COMMAND_ERROR_DATALOSS 142 
#define  GVE_ADMINQ_COMMAND_ERROR_DEADLINE_EXCEEDED 141 
#define  GVE_ADMINQ_COMMAND_ERROR_FAILED_PRECONDITION 140 
#define  GVE_ADMINQ_COMMAND_ERROR_INTERNAL_ERROR 139 
#define  GVE_ADMINQ_COMMAND_ERROR_INVALID_ARGUMENT 138 
#define  GVE_ADMINQ_COMMAND_ERROR_NOT_FOUND 137 
#define  GVE_ADMINQ_COMMAND_ERROR_OUT_OF_RANGE 136 
#define  GVE_ADMINQ_COMMAND_ERROR_PERMISSION_DENIED 135 
#define  GVE_ADMINQ_COMMAND_ERROR_RESOURCE_EXHAUSTED 134 
#define  GVE_ADMINQ_COMMAND_ERROR_UNAUTHENTICATED 133 
#define  GVE_ADMINQ_COMMAND_ERROR_UNAVAILABLE 132 
#define  GVE_ADMINQ_COMMAND_ERROR_UNIMPLEMENTED 131 
#define  GVE_ADMINQ_COMMAND_ERROR_UNKNOWN_ERROR 130 
#define  GVE_ADMINQ_COMMAND_PASSED 129 
#define  GVE_ADMINQ_COMMAND_UNSET 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 

__attribute__((used)) static int gve_adminq_parse_err(struct device *dev, u32 status)
{
	if (status != GVE_ADMINQ_COMMAND_PASSED &&
	    status != GVE_ADMINQ_COMMAND_UNSET)
		dev_err(dev, "AQ command failed with status %d\n", status);

	switch (status) {
	case GVE_ADMINQ_COMMAND_PASSED:
		return 0;
	case GVE_ADMINQ_COMMAND_UNSET:
		dev_err(dev, "parse_aq_err: err and status both unset, this should not be possible.\n");
		return -EINVAL;
	case GVE_ADMINQ_COMMAND_ERROR_ABORTED:
	case GVE_ADMINQ_COMMAND_ERROR_CANCELLED:
	case GVE_ADMINQ_COMMAND_ERROR_DATALOSS:
	case GVE_ADMINQ_COMMAND_ERROR_FAILED_PRECONDITION:
	case GVE_ADMINQ_COMMAND_ERROR_UNAVAILABLE:
		return -EAGAIN;
	case GVE_ADMINQ_COMMAND_ERROR_ALREADY_EXISTS:
	case GVE_ADMINQ_COMMAND_ERROR_INTERNAL_ERROR:
	case GVE_ADMINQ_COMMAND_ERROR_INVALID_ARGUMENT:
	case GVE_ADMINQ_COMMAND_ERROR_NOT_FOUND:
	case GVE_ADMINQ_COMMAND_ERROR_OUT_OF_RANGE:
	case GVE_ADMINQ_COMMAND_ERROR_UNKNOWN_ERROR:
		return -EINVAL;
	case GVE_ADMINQ_COMMAND_ERROR_DEADLINE_EXCEEDED:
		return -ETIME;
	case GVE_ADMINQ_COMMAND_ERROR_PERMISSION_DENIED:
	case GVE_ADMINQ_COMMAND_ERROR_UNAUTHENTICATED:
		return -EACCES;
	case GVE_ADMINQ_COMMAND_ERROR_RESOURCE_EXHAUSTED:
		return -ENOMEM;
	case GVE_ADMINQ_COMMAND_ERROR_UNIMPLEMENTED:
		return -ENOTSUPP;
	default:
		dev_err(dev, "parse_aq_err: unknown status code %d\n", status);
		return -EINVAL;
	}
}