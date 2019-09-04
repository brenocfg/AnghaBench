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
struct atmtcp_dev_data {scalar_t__ persist; int /*<<< orphan*/ * vcc; } ;
struct atm_vcc {int /*<<< orphan*/ * dev_data; } ;
struct atm_dev {int /*<<< orphan*/ * dev_data; } ;

/* Variables and functions */
 struct atmtcp_dev_data* PRIV (struct atm_dev*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atm_dev_deregister (struct atm_dev*) ; 
 int /*<<< orphan*/  kfree (struct atmtcp_dev_data*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmtcp_c_close(struct atm_vcc *vcc)
{
	struct atm_dev *atmtcp_dev;
	struct atmtcp_dev_data *dev_data;

	atmtcp_dev = (struct atm_dev *) vcc->dev_data;
	dev_data = PRIV(atmtcp_dev);
	dev_data->vcc = NULL;
	if (dev_data->persist) return;
	atmtcp_dev->dev_data = NULL;
	kfree(dev_data);
	atm_dev_deregister(atmtcp_dev);
	vcc->dev_data = NULL;
	module_put(THIS_MODULE);
}