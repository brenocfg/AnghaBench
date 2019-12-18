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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rio_mport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDT_RIO_DOMAIN ; 
 int /*<<< orphan*/  rio_mport_write_config_32 (struct rio_mport*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
idtg2_set_domain(struct rio_mport *mport, u16 destid, u8 hopcount,
		       u8 sw_domain)
{
	/*
	 * Switch domain configuration operates only at global level
	 */
	rio_mport_write_config_32(mport, destid, hopcount,
				  IDT_RIO_DOMAIN, (u32)sw_domain);
	return 0;
}