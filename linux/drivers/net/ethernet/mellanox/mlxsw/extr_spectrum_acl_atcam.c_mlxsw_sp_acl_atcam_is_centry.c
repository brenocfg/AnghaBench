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
struct mlxsw_sp_acl_atcam_entry {int /*<<< orphan*/  erp_mask; } ;

/* Variables and functions */
 int mlxsw_sp_acl_erp_mask_is_ctcam (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mlxsw_sp_acl_atcam_is_centry(const struct mlxsw_sp_acl_atcam_entry *aentry)
{
	return mlxsw_sp_acl_erp_mask_is_ctcam(aentry->erp_mask);
}