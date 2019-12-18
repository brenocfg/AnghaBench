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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_fw_runtime {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_fw_trigger_timestamp (struct iwl_fw_runtime*,int /*<<< orphan*/ ) ; 
 int kstrtou32 (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_timestamp_marker_write(struct iwl_fw_runtime *fwrt,
						char *buf, size_t count)
{
	int ret;
	u32 delay;

	ret = kstrtou32(buf, 10, &delay);
	if (ret < 0)
		return ret;

	iwl_fw_trigger_timestamp(fwrt, delay);

	return count;
}