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
struct drm_dp_aux {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_AUX_NATIVE_WRITE ; 
 int drm_dp_dpcd_access (struct drm_dp_aux*,int /*<<< orphan*/ ,unsigned int,void*,size_t) ; 
 int /*<<< orphan*/  drm_dp_dump_access (struct drm_dp_aux*,int /*<<< orphan*/ ,unsigned int,void*,int) ; 

ssize_t drm_dp_dpcd_write(struct drm_dp_aux *aux, unsigned int offset,
			  void *buffer, size_t size)
{
	int ret;

	ret = drm_dp_dpcd_access(aux, DP_AUX_NATIVE_WRITE, offset, buffer,
				 size);
	drm_dp_dump_access(aux, DP_AUX_NATIVE_WRITE, offset, buffer, ret);
	return ret;
}