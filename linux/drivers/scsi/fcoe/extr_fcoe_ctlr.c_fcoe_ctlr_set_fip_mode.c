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
struct fcoe_ctlr_device {int mode; } ;
struct fcoe_ctlr {int /*<<< orphan*/  mode; int /*<<< orphan*/  ctlr_mutex; struct fc_lport* lp; } ;
struct fc_lport {int dummy; } ;

/* Variables and functions */
#define  FIP_CONN_TYPE_FABRIC 129 
#define  FIP_CONN_TYPE_VN2VN 128 
 int /*<<< orphan*/  FIP_MODE_FABRIC ; 
 int /*<<< orphan*/  FIP_MODE_VN2VN ; 
 struct fcoe_ctlr* fcoe_ctlr_device_priv (struct fcoe_ctlr_device*) ; 
 int /*<<< orphan*/  fcoe_ctlr_mode_set (struct fc_lport*,struct fcoe_ctlr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void fcoe_ctlr_set_fip_mode(struct fcoe_ctlr_device *ctlr_dev)
{
	struct fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);
	struct fc_lport *lport = ctlr->lp;

	mutex_lock(&ctlr->ctlr_mutex);
	switch (ctlr_dev->mode) {
	case FIP_CONN_TYPE_VN2VN:
		ctlr->mode = FIP_MODE_VN2VN;
		break;
	case FIP_CONN_TYPE_FABRIC:
	default:
		ctlr->mode = FIP_MODE_FABRIC;
		break;
	}

	mutex_unlock(&ctlr->ctlr_mutex);

	fcoe_ctlr_mode_set(lport, ctlr, ctlr->mode);
}