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
struct tb {scalar_t__ nboot_acl; int /*<<< orphan*/  security_level; } ;
struct icm {scalar_t__ max_boot_acl; int /*<<< orphan*/  rpm; scalar_t__ safe_mode; } ;

/* Variables and functions */
 int __icm_driver_ready (struct tb*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int icm_firmware_init (struct tb*) ; 
 int /*<<< orphan*/  tb_info (struct tb*,char*) ; 
 struct icm* tb_priv (struct tb*) ; 

__attribute__((used)) static int icm_driver_ready(struct tb *tb)
{
	struct icm *icm = tb_priv(tb);
	int ret;

	ret = icm_firmware_init(tb);
	if (ret)
		return ret;

	if (icm->safe_mode) {
		tb_info(tb, "Thunderbolt host controller is in safe mode.\n");
		tb_info(tb, "You need to update NVM firmware of the controller before it can be used.\n");
		tb_info(tb, "For latest updates check https://thunderbolttechnology.net/updates.\n");
		return 0;
	}

	ret = __icm_driver_ready(tb, &tb->security_level, &tb->nboot_acl,
				 &icm->rpm);
	if (ret)
		return ret;

	/*
	 * Make sure the number of supported preboot ACL matches what we
	 * expect or disable the whole feature.
	 */
	if (tb->nboot_acl > icm->max_boot_acl)
		tb->nboot_acl = 0;

	return 0;
}