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
struct ionic_dev {int dummy; } ;
struct ionic {int /*<<< orphan*/  dev_cmd_lock; struct ionic_dev idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCMD_TIMEOUT ; 
 int /*<<< orphan*/  ionic_dev_cmd_reset (struct ionic_dev*) ; 
 int ionic_dev_cmd_wait (struct ionic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ionic_reset(struct ionic *ionic)
{
	struct ionic_dev *idev = &ionic->idev;
	int err;

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_reset(idev);
	err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&ionic->dev_cmd_lock);

	return err;
}