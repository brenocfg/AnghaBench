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
struct malidp_hw_device {TYPE_1__* hw; } ;
struct malidp_drm {int /*<<< orphan*/  config_valid; int /*<<< orphan*/  wq; struct malidp_hw_device* dev; } ;
struct drm_device {struct malidp_drm* dev_private; } ;
struct TYPE_2__ {scalar_t__ (* in_config_mode ) (struct malidp_hw_device*) ;int /*<<< orphan*/  (* set_config_valid ) (struct malidp_hw_device*,int) ;} ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ MALIDP_CONFIG_VALID_DONE ; 
 int /*<<< orphan*/  MALIDP_CONF_VALID_TIMEOUT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct malidp_hw_device*,int) ; 
 scalar_t__ stub2 (struct malidp_hw_device*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int malidp_set_and_wait_config_valid(struct drm_device *drm)
{
	struct malidp_drm *malidp = drm->dev_private;
	struct malidp_hw_device *hwdev = malidp->dev;
	int ret;

	hwdev->hw->set_config_valid(hwdev, 1);
	/* don't wait for config_valid flag if we are in config mode */
	if (hwdev->hw->in_config_mode(hwdev)) {
		atomic_set(&malidp->config_valid, MALIDP_CONFIG_VALID_DONE);
		return 0;
	}

	ret = wait_event_interruptible_timeout(malidp->wq,
			atomic_read(&malidp->config_valid) == MALIDP_CONFIG_VALID_DONE,
			msecs_to_jiffies(MALIDP_CONF_VALID_TIMEOUT));

	return (ret > 0) ? 0 : -ETIMEDOUT;
}