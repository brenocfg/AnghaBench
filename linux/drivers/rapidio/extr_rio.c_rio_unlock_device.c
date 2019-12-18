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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rio_mport {int /*<<< orphan*/  host_deviceid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RIO_HOST_DID_LOCK_CSR ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rio_mport_read_config_32 (struct rio_mport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rio_mport_write_config_32 (struct rio_mport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rio_unlock_device(struct rio_mport *port, u16 destid, u8 hopcount)
{
	u32 result;

	/* Release device lock */
	rio_mport_write_config_32(port, destid,
				  hopcount,
				  RIO_HOST_DID_LOCK_CSR,
				  port->host_deviceid);
	rio_mport_read_config_32(port, destid, hopcount,
		RIO_HOST_DID_LOCK_CSR, &result);
	if ((result & 0xffff) != 0xffff) {
		pr_debug("RIO: badness when releasing device lock %x:%x\n",
			 destid, hopcount);
		return -EINVAL;
	}

	return 0;
}