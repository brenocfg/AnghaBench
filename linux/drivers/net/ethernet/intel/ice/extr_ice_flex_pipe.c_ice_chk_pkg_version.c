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
struct ice_pkg_ver {scalar_t__ major; scalar_t__ minor; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_NOT_SUPPORTED ; 
 scalar_t__ ICE_PKG_SUPP_VER_MAJ ; 
 scalar_t__ ICE_PKG_SUPP_VER_MNR ; 

__attribute__((used)) static enum ice_status ice_chk_pkg_version(struct ice_pkg_ver *pkg_ver)
{
	if (pkg_ver->major != ICE_PKG_SUPP_VER_MAJ ||
	    pkg_ver->minor != ICE_PKG_SUPP_VER_MNR)
		return ICE_ERR_NOT_SUPPORTED;

	return 0;
}