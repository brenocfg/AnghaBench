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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 struct dsaf_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_dsaf_ae_uninit (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_free (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_free_dev (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_mac_uninit (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_ppe_uninit (struct dsaf_device*) ; 

__attribute__((used)) static int hns_dsaf_remove(struct platform_device *pdev)
{
	struct dsaf_device *dsaf_dev = dev_get_drvdata(&pdev->dev);

	hns_dsaf_ae_uninit(dsaf_dev);

	hns_ppe_uninit(dsaf_dev);

	hns_mac_uninit(dsaf_dev);

	hns_dsaf_free(dsaf_dev);

	hns_dsaf_free_dev(dsaf_dev);

	return 0;
}