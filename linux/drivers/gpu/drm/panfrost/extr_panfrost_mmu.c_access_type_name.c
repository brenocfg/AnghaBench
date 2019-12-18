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
struct panfrost_device {int dummy; } ;

/* Variables and functions */
#define  AS_FAULTSTATUS_ACCESS_TYPE_ATOMIC 131 
#define  AS_FAULTSTATUS_ACCESS_TYPE_EX 130 
 int AS_FAULTSTATUS_ACCESS_TYPE_MASK ; 
#define  AS_FAULTSTATUS_ACCESS_TYPE_READ 129 
#define  AS_FAULTSTATUS_ACCESS_TYPE_WRITE 128 
 int /*<<< orphan*/  HW_FEATURE_AARCH64_MMU ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  panfrost_has_hw_feature (struct panfrost_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *access_type_name(struct panfrost_device *pfdev,
		u32 fault_status)
{
	switch (fault_status & AS_FAULTSTATUS_ACCESS_TYPE_MASK) {
	case AS_FAULTSTATUS_ACCESS_TYPE_ATOMIC:
		if (panfrost_has_hw_feature(pfdev, HW_FEATURE_AARCH64_MMU))
			return "ATOMIC";
		else
			return "UNKNOWN";
	case AS_FAULTSTATUS_ACCESS_TYPE_READ:
		return "READ";
	case AS_FAULTSTATUS_ACCESS_TYPE_WRITE:
		return "WRITE";
	case AS_FAULTSTATUS_ACCESS_TYPE_EX:
		return "EXECUTE";
	default:
		WARN_ON(1);
		return NULL;
	}
}