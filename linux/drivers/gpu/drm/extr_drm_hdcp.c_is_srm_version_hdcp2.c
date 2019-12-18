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
typedef  scalar_t__ const u8 ;

/* Variables and functions */
 int DRM_HDCP_2_INDICATOR ; 
 int DRM_HDCP_2_SRM_ID ; 

__attribute__((used)) static inline bool is_srm_version_hdcp2(const u8 *buf)
{
	return *buf == (u8)(DRM_HDCP_2_SRM_ID << 4 | DRM_HDCP_2_INDICATOR);
}