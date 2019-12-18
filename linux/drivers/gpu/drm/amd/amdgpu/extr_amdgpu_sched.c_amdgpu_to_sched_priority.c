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
typedef  enum drm_sched_priority { ____Placeholder_drm_sched_priority } drm_sched_priority ;

/* Variables and functions */
#define  AMDGPU_CTX_PRIORITY_HIGH 133 
#define  AMDGPU_CTX_PRIORITY_LOW 132 
#define  AMDGPU_CTX_PRIORITY_NORMAL 131 
#define  AMDGPU_CTX_PRIORITY_UNSET 130 
#define  AMDGPU_CTX_PRIORITY_VERY_HIGH 129 
#define  AMDGPU_CTX_PRIORITY_VERY_LOW 128 
 int DRM_SCHED_PRIORITY_HIGH_HW ; 
 int DRM_SCHED_PRIORITY_HIGH_SW ; 
 int DRM_SCHED_PRIORITY_INVALID ; 
 int DRM_SCHED_PRIORITY_LOW ; 
 int DRM_SCHED_PRIORITY_NORMAL ; 
 int DRM_SCHED_PRIORITY_UNSET ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 

enum drm_sched_priority amdgpu_to_sched_priority(int amdgpu_priority)
{
	switch (amdgpu_priority) {
	case AMDGPU_CTX_PRIORITY_VERY_HIGH:
		return DRM_SCHED_PRIORITY_HIGH_HW;
	case AMDGPU_CTX_PRIORITY_HIGH:
		return DRM_SCHED_PRIORITY_HIGH_SW;
	case AMDGPU_CTX_PRIORITY_NORMAL:
		return DRM_SCHED_PRIORITY_NORMAL;
	case AMDGPU_CTX_PRIORITY_LOW:
	case AMDGPU_CTX_PRIORITY_VERY_LOW:
		return DRM_SCHED_PRIORITY_LOW;
	case AMDGPU_CTX_PRIORITY_UNSET:
		return DRM_SCHED_PRIORITY_UNSET;
	default:
		WARN(1, "Invalid context priority %d\n", amdgpu_priority);
		return DRM_SCHED_PRIORITY_INVALID;
	}
}