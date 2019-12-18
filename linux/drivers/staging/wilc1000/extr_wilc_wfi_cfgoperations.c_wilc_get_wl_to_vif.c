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
struct wilc_vif {int dummy; } ;
struct wilc {int vif_num; struct wilc_vif** vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct wilc_vif* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wilc_vif *wilc_get_wl_to_vif(struct wilc *wl)
{
	int i;

	for (i = 0; i < wl->vif_num; i++)
		if (wl->vif[i])
			return wl->vif[i];

	return ERR_PTR(-EINVAL);
}