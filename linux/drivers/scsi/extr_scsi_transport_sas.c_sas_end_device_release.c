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
struct sas_rphy {scalar_t__ q; } ;
struct sas_end_device {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 struct sas_rphy* dev_to_rphy (struct device*) ; 
 int /*<<< orphan*/  kfree (struct sas_end_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 struct sas_end_device* rphy_to_end_device (struct sas_rphy*) ; 

__attribute__((used)) static void sas_end_device_release(struct device *dev)
{
	struct sas_rphy *rphy = dev_to_rphy(dev);
	struct sas_end_device *edev = rphy_to_end_device(rphy);

	if (rphy->q)
		blk_cleanup_queue(rphy->q);

	put_device(dev->parent);
	kfree(edev);
}