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
 int /*<<< orphan*/  DBF_INFO ; 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_bus_force_rescan () ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcrypt_rescan_count ; 
 int /*<<< orphan*/  zcrypt_rescan_req ; 

__attribute__((used)) static inline int zcrypt_process_rescan(void)
{
	if (atomic_read(&zcrypt_rescan_req)) {
		atomic_set(&zcrypt_rescan_req, 0);
		atomic_inc(&zcrypt_rescan_count);
		ap_bus_force_rescan();
		ZCRYPT_DBF(DBF_INFO, "rescan count=%07d\n",
			   atomic_inc_return(&zcrypt_rescan_count));
		return 1;
	}
	return 0;
}