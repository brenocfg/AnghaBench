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

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int NV_DPMS_CLEARED ; 

__attribute__((used)) static inline bool is_powersaving_dpms(int mode)
{
	return mode != DRM_MODE_DPMS_ON && mode != NV_DPMS_CLEARED;
}