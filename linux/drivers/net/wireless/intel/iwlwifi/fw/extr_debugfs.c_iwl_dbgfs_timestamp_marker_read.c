#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  delay; } ;
struct iwl_fw_runtime {TYPE_1__ timestamp; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_timestamp_marker_read(struct iwl_fw_runtime *fwrt,
					       size_t size, char *buf)
{
	u32 delay_secs = jiffies_to_msecs(fwrt->timestamp.delay) / 1000;

	return scnprintf(buf, size, "%d\n", delay_secs);
}