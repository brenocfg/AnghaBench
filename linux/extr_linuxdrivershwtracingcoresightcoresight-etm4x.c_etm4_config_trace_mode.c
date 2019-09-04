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
struct etmv4_config {int mode; int* addr_acc; } ;

/* Variables and functions */
 size_t ETM_DEFAULT_ADDR_COMP ; 
 int ETM_EXLEVEL_NS_APP ; 
 int ETM_EXLEVEL_NS_OS ; 
 int ETM_MODE_EXCL_KERN ; 
 int ETM_MODE_EXCL_USER ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

void etm4_config_trace_mode(struct etmv4_config *config)
{
	u32 addr_acc, mode;

	mode = config->mode;
	mode &= (ETM_MODE_EXCL_KERN | ETM_MODE_EXCL_USER);

	/* excluding kernel AND user space doesn't make sense */
	WARN_ON_ONCE(mode == (ETM_MODE_EXCL_KERN | ETM_MODE_EXCL_USER));

	/* nothing to do if neither flags are set */
	if (!(mode & ETM_MODE_EXCL_KERN) && !(mode & ETM_MODE_EXCL_USER))
		return;

	addr_acc = config->addr_acc[ETM_DEFAULT_ADDR_COMP];
	/* clear default config */
	addr_acc &= ~(ETM_EXLEVEL_NS_APP | ETM_EXLEVEL_NS_OS);

	/*
	 * EXLEVEL_NS, bits[15:12]
	 * The Exception levels are:
	 *   Bit[12] Exception level 0 - Application
	 *   Bit[13] Exception level 1 - OS
	 *   Bit[14] Exception level 2 - Hypervisor
	 *   Bit[15] Never implemented
	 */
	if (mode & ETM_MODE_EXCL_KERN)
		addr_acc |= ETM_EXLEVEL_NS_OS;
	else
		addr_acc |= ETM_EXLEVEL_NS_APP;

	config->addr_acc[ETM_DEFAULT_ADDR_COMP] = addr_acc;
	config->addr_acc[ETM_DEFAULT_ADDR_COMP + 1] = addr_acc;
}