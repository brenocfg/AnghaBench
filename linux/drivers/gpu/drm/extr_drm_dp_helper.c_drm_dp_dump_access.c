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
typedef  int /*<<< orphan*/  uint ;
typedef  scalar_t__ u8 ;
struct drm_dp_aux {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DP_AUX_NATIVE_READ ; 
 int /*<<< orphan*/  DRM_DEBUG_DP (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,...) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static inline void
drm_dp_dump_access(const struct drm_dp_aux *aux,
		   u8 request, uint offset, void *buffer, int ret)
{
	const char *arrow = request == DP_AUX_NATIVE_READ ? "->" : "<-";

	if (ret > 0)
		DRM_DEBUG_DP("%s: 0x%05x AUX %s (ret=%3d) %*ph\n",
			     aux->name, offset, arrow, ret, min(ret, 20), buffer);
	else
		DRM_DEBUG_DP("%s: 0x%05x AUX %s (ret=%3d)\n",
			     aux->name, offset, arrow, ret);
}