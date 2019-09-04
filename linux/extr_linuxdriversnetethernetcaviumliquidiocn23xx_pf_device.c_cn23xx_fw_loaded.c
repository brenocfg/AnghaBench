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
typedef  unsigned long long u64 ;
struct octeon_device {int /*<<< orphan*/  adapter_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN23XX_SLI_SCRATCH2 ; 
 unsigned long long SCR2_BIT_FW_LOADED ; 
 int atomic_read (int /*<<< orphan*/ ) ; 
 unsigned long long octeon_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 

int cn23xx_fw_loaded(struct octeon_device *oct)
{
	u64 val;

	/* If there's more than one active PF on this NIC, then that
	 * implies that the NIC firmware is loaded and running.  This check
	 * prevents a rare false negative that might occur if we only relied
	 * on checking the SCR2_BIT_FW_LOADED flag.  The false negative would
	 * happen if the PF driver sees SCR2_BIT_FW_LOADED as cleared even
	 * though the firmware was already loaded but still booting and has yet
	 * to set SCR2_BIT_FW_LOADED.
	 */
	if (atomic_read(oct->adapter_refcount) > 1)
		return 1;

	val = octeon_read_csr64(oct, CN23XX_SLI_SCRATCH2);
	return (val >> SCR2_BIT_FW_LOADED) & 1ULL;
}