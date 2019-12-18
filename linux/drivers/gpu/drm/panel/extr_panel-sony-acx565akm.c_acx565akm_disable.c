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
struct drm_panel {int dummy; } ;
struct acx565akm_panel {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  acx565akm_power_off (struct acx565akm_panel*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct acx565akm_panel* to_acx565akm_device (struct drm_panel*) ; 

__attribute__((used)) static int acx565akm_disable(struct drm_panel *panel)
{
	struct acx565akm_panel *lcd = to_acx565akm_device(panel);

	mutex_lock(&lcd->mutex);
	acx565akm_power_off(lcd);
	mutex_unlock(&lcd->mutex);

	return 0;
}