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
struct i40e_vsi {int /*<<< orphan*/ * rss_lut_user; int /*<<< orphan*/ * rss_hkey_user; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40e_clear_rss_config_user(struct i40e_vsi *vsi)
{
	if (!vsi)
		return;

	kfree(vsi->rss_hkey_user);
	vsi->rss_hkey_user = NULL;

	kfree(vsi->rss_lut_user);
	vsi->rss_lut_user = NULL;
}