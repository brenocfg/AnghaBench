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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  addrconf_addr_eui48 (char*,char const* const) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
usnic_mac_ip_to_gid(const char *const mac, const __be32 inaddr, char *raw_gid)
{
	raw_gid[0] = 0xfe;
	raw_gid[1] = 0x80;
	memset(&raw_gid[2], 0, 2);
	memcpy(&raw_gid[4], &inaddr, 4);
	addrconf_addr_eui48(&raw_gid[8], mac);
}