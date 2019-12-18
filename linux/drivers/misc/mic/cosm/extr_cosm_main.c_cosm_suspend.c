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
struct device {int dummy; } ;
struct cosm_device {int state; int /*<<< orphan*/  cosm_mutex; } ;

/* Variables and functions */
#define  MIC_BOOTING 130 
#define  MIC_ONLINE 129 
#define  MIC_SHUTTING_DOWN 128 
 int /*<<< orphan*/  cosm_stop (struct cosm_device*,int) ; 
 struct cosm_device* dev_to_cosm (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cosm_suspend(struct device *dev)
{
	struct cosm_device *cdev = dev_to_cosm(dev);

	mutex_lock(&cdev->cosm_mutex);
	switch (cdev->state) {
	/**
	 * Suspend/freeze hooks in userspace have already shutdown the card.
	 * Card should be 'ready' in most cases. It is however possible that
	 * some userspace application initiated a boot. In those cases, we
	 * simply reset the card.
	 */
	case MIC_ONLINE:
	case MIC_BOOTING:
	case MIC_SHUTTING_DOWN:
		mutex_unlock(&cdev->cosm_mutex);
		cosm_stop(cdev, false);
		break;
	default:
		mutex_unlock(&cdev->cosm_mutex);
		break;
	}
	return 0;
}