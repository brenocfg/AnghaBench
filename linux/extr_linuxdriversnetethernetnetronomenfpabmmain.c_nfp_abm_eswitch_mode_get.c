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
struct nfp_app {struct nfp_abm* priv; } ;
struct nfp_abm {int eswitch_mode; } ;
typedef  enum devlink_eswitch_mode { ____Placeholder_devlink_eswitch_mode } devlink_eswitch_mode ;

/* Variables and functions */

__attribute__((used)) static enum devlink_eswitch_mode nfp_abm_eswitch_mode_get(struct nfp_app *app)
{
	struct nfp_abm *abm = app->priv;

	return abm->eswitch_mode;
}