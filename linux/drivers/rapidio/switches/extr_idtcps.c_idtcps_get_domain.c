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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rio_mport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDTCPS_RIO_DOMAIN ; 
 int /*<<< orphan*/  rio_mport_read_config_32 (struct rio_mport*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
idtcps_get_domain(struct rio_mport *mport, u16 destid, u8 hopcount,
		       u8 *sw_domain)
{
	u32 regval;

	/*
	 * Switch domain configuration operates only at global level
	 */
	rio_mport_read_config_32(mport, destid, hopcount,
				IDTCPS_RIO_DOMAIN, &regval);

	*sw_domain = (u8)(regval & 0xff);

	return 0;
}