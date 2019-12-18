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
struct ionic_identity {int /*<<< orphan*/  port; } ;
struct ionic_dev {TYPE_1__* dev_cmd_regs; } ;
struct ionic {int /*<<< orphan*/  dev_cmd_lock; struct ionic_dev idev; struct ionic_identity ident; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCMD_TIMEOUT ; 
 int /*<<< orphan*/  ionic_dev_cmd_port_identify (struct ionic_dev*) ; 
 int ionic_dev_cmd_wait (struct ionic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t min (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ionic_port_identify(struct ionic *ionic)
{
	struct ionic_identity *ident = &ionic->ident;
	struct ionic_dev *idev = &ionic->idev;
	size_t sz;
	int err;

	mutex_lock(&ionic->dev_cmd_lock);

	ionic_dev_cmd_port_identify(idev);
	err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	if (!err) {
		sz = min(sizeof(ident->port), sizeof(idev->dev_cmd_regs->data));
		memcpy_fromio(&ident->port, &idev->dev_cmd_regs->data, sz);
	}

	mutex_unlock(&ionic->dev_cmd_lock);

	return err;
}