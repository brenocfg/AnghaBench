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
typedef  int u64 ;
struct etmv4_config {int mode; } ;

/* Variables and functions */
 int ETM_EXLEVEL_NS_APP ; 
 int ETM_EXLEVEL_NS_HYP ; 
 int ETM_EXLEVEL_NS_OS ; 
 int ETM_EXLEVEL_S_APP ; 
 int ETM_EXLEVEL_S_HYP ; 
 int ETM_EXLEVEL_S_OS ; 
 int ETM_MODE_EXCL_KERN ; 
 int ETM_MODE_EXCL_USER ; 

__attribute__((used)) static u64 etm4_get_access_type(struct etmv4_config *config)
{
	u64 access_type = 0;

	/*
	 * EXLEVEL_NS, bits[15:12]
	 * The Exception levels are:
	 *   Bit[12] Exception level 0 - Application
	 *   Bit[13] Exception level 1 - OS
	 *   Bit[14] Exception level 2 - Hypervisor
	 *   Bit[15] Never implemented
	 *
	 * Always stay away from hypervisor mode.
	 */
	access_type = ETM_EXLEVEL_NS_HYP;

	if (config->mode & ETM_MODE_EXCL_KERN)
		access_type |= ETM_EXLEVEL_NS_OS;

	if (config->mode & ETM_MODE_EXCL_USER)
		access_type |= ETM_EXLEVEL_NS_APP;

	/*
	 * EXLEVEL_S, bits[11:8], don't trace anything happening
	 * in secure state.
	 */
	access_type |= (ETM_EXLEVEL_S_APP	|
			ETM_EXLEVEL_S_OS	|
			ETM_EXLEVEL_S_HYP);

	return access_type;
}