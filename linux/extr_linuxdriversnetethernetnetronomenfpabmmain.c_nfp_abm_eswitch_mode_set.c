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
typedef  int u16 ;
struct nfp_app {struct nfp_abm* priv; } ;
struct nfp_abm {int eswitch_mode; } ;

/* Variables and functions */
#define  DEVLINK_ESWITCH_MODE_LEGACY 129 
#define  DEVLINK_ESWITCH_MODE_SWITCHDEV 128 
 int EINVAL ; 
 int nfp_abm_eswitch_set_legacy (struct nfp_abm*) ; 
 int nfp_abm_eswitch_set_switchdev (struct nfp_abm*) ; 

__attribute__((used)) static int nfp_abm_eswitch_mode_set(struct nfp_app *app, u16 mode)
{
	struct nfp_abm *abm = app->priv;

	if (abm->eswitch_mode == mode)
		return 0;

	switch (mode) {
	case DEVLINK_ESWITCH_MODE_LEGACY:
		return nfp_abm_eswitch_set_legacy(abm);
	case DEVLINK_ESWITCH_MODE_SWITCHDEV:
		return nfp_abm_eswitch_set_switchdev(abm);
	default:
		return -EINVAL;
	}
}