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
struct msi2500_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msi2500_iso_free (struct msi2500_dev*) ; 
 int /*<<< orphan*/  msi2500_iso_stop (struct msi2500_dev*) ; 

__attribute__((used)) static void msi2500_isoc_cleanup(struct msi2500_dev *dev)
{
	dev_dbg(dev->dev, "\n");

	msi2500_iso_stop(dev);
	msi2500_iso_free(dev);
}