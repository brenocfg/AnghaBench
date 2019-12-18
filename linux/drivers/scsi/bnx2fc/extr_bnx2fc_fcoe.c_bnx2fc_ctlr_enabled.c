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
struct fcoe_ctlr_device {int enabled; } ;
struct fcoe_ctlr {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  FCOE_CTLR_DISABLED 130 
#define  FCOE_CTLR_ENABLED 129 
#define  FCOE_CTLR_UNUSED 128 
 int __bnx2fc_disable (struct fcoe_ctlr*) ; 
 int __bnx2fc_enable (struct fcoe_ctlr*) ; 
 struct fcoe_ctlr* fcoe_ctlr_device_priv (struct fcoe_ctlr_device*) ; 

__attribute__((used)) static int bnx2fc_ctlr_enabled(struct fcoe_ctlr_device *cdev)
{
	struct fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(cdev);

	switch (cdev->enabled) {
	case FCOE_CTLR_ENABLED:
		return __bnx2fc_enable(ctlr);
	case FCOE_CTLR_DISABLED:
		return __bnx2fc_disable(ctlr);
	case FCOE_CTLR_UNUSED:
	default:
		return -ENOTSUPP;
	};
}