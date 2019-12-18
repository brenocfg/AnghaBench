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
typedef  int u8 ;
struct mwifiex_adapter {int /*<<< orphan*/  fw_release_number; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 char* driver_version ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 

int
mwifiex_drv_get_driver_version(struct mwifiex_adapter *adapter, char *version,
			       int max_len)
{
	union {
		__le32 l;
		u8 c[4];
	} ver;
	char fw_ver[32];

	ver.l = cpu_to_le32(adapter->fw_release_number);
	sprintf(fw_ver, "%u.%u.%u.p%u", ver.c[2], ver.c[1], ver.c[0], ver.c[3]);

	snprintf(version, max_len, driver_version, fw_ver);

	mwifiex_dbg(adapter, MSG, "info: MWIFIEX VERSION: %s\n", version);

	return 0;
}