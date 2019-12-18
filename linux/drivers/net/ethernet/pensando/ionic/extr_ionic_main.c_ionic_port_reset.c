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
struct ionic_dev {scalar_t__ port_info_pa; int /*<<< orphan*/ * port_info; int /*<<< orphan*/  port_info_sz; } ;
struct ionic {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_cmd_lock; struct ionic_dev idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCMD_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ionic_dev_cmd_port_reset (struct ionic_dev*) ; 
 int ionic_dev_cmd_wait (struct ionic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ionic_port_reset(struct ionic *ionic)
{
	struct ionic_dev *idev = &ionic->idev;
	int err;

	if (!idev->port_info)
		return 0;

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_port_reset(idev);
	err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&ionic->dev_cmd_lock);

	dma_free_coherent(ionic->dev, idev->port_info_sz,
			  idev->port_info, idev->port_info_pa);

	idev->port_info = NULL;
	idev->port_info_pa = 0;

	if (err)
		dev_err(ionic->dev, "Failed to reset port\n");

	return err;
}