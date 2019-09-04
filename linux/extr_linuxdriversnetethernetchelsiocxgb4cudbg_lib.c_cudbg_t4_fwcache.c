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
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int sys_warn; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PARAM_DEV_FWCACHE_FLUSH ; 
 scalar_t__ is_fw_attached (struct cudbg_init*) ; 
 int t4_fwcache (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cudbg_t4_fwcache(struct cudbg_init *pdbg_init,
			     struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	int rc;

	if (is_fw_attached(pdbg_init)) {
		/* Flush uP dcache before reading edcX/mcX  */
		rc = t4_fwcache(padap, FW_PARAM_DEV_FWCACHE_FLUSH);
		if (rc)
			cudbg_err->sys_warn = rc;
	}
}