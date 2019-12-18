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
struct mei_fw_status {int count; int /*<<< orphan*/ * status; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t MEI_FW_STATUS_STR_SZ ; 
 scalar_t__ scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 

ssize_t mei_fw_status2str(struct mei_fw_status *fw_status,
			  char *buf, size_t len)
{
	ssize_t cnt = 0;
	int i;

	buf[0] = '\0';

	if (len < MEI_FW_STATUS_STR_SZ)
		return -EINVAL;

	for (i = 0; i < fw_status->count; i++)
		cnt += scnprintf(buf + cnt, len - cnt, "%08X ",
				fw_status->status[i]);

	/* drop last space */
	buf[cnt] = '\0';
	return cnt;
}