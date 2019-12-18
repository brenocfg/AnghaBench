#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fcoe_ctlr_device {int dummy; } ;
struct fcoe_ctlr {TYPE_1__* lp; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int r_a_tov; } ;

/* Variables and functions */
 struct fcoe_ctlr_device* dev_to_ctlr (struct device*) ; 
 struct fcoe_ctlr* fcoe_ctlr_device_priv (struct fcoe_ctlr_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_ctlr_r_a_tov(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct fcoe_ctlr_device *ctlr_dev = dev_to_ctlr(dev);
	struct fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);

	return sprintf(buf, "%d\n", ctlr->lp->r_a_tov);
}