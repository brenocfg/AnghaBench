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
struct wilc {int vif_num; int /*<<< orphan*/  vif_mutex; TYPE_1__** vif; } ;
struct TYPE_2__ {int iftype; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wilc_get_vif_from_type(struct wilc *wl, int type)
{
	int i;

	mutex_lock(&wl->vif_mutex);
	for (i = 0; i < wl->vif_num; i++) {
		if (wl->vif[i]->iftype == type) {
			mutex_unlock(&wl->vif_mutex);
			return i;
		}
	}
	mutex_unlock(&wl->vif_mutex);

	return -EINVAL;
}