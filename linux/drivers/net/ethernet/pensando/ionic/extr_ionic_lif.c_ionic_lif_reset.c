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
struct ionic_lif {TYPE_1__* ionic; int /*<<< orphan*/  index; } ;
struct ionic_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_cmd_lock; struct ionic_dev idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCMD_TIMEOUT ; 
 int /*<<< orphan*/  ionic_dev_cmd_lif_reset (struct ionic_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_dev_cmd_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ionic_lif_reset(struct ionic_lif *lif)
{
	struct ionic_dev *idev = &lif->ionic->idev;

	mutex_lock(&lif->ionic->dev_cmd_lock);
	ionic_dev_cmd_lif_reset(idev, lif->index);
	ionic_dev_cmd_wait(lif->ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&lif->ionic->dev_cmd_lock);
}