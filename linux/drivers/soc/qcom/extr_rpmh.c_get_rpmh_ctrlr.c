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
struct rpmh_ctrlr {int dummy; } ;
struct rsc_drv {struct rpmh_ctrlr client; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct rsc_drv* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpmh_ctrlr *get_rpmh_ctrlr(const struct device *dev)
{
	struct rsc_drv *drv = dev_get_drvdata(dev->parent);

	return &drv->client;
}