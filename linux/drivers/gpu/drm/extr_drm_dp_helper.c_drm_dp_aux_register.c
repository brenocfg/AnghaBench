#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  class; int /*<<< orphan*/  algo; } ;
struct drm_dp_aux {TYPE_2__ ddc; int /*<<< orphan*/  dev; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_aux_init (struct drm_dp_aux*) ; 
 int drm_dp_aux_register_devnode (struct drm_dp_aux*) ; 
 int /*<<< orphan*/  drm_dp_aux_unregister_devnode (struct drm_dp_aux*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 

int drm_dp_aux_register(struct drm_dp_aux *aux)
{
	int ret;

	if (!aux->ddc.algo)
		drm_dp_aux_init(aux);

	aux->ddc.class = I2C_CLASS_DDC;
	aux->ddc.owner = THIS_MODULE;
	aux->ddc.dev.parent = aux->dev;

	strlcpy(aux->ddc.name, aux->name ? aux->name : dev_name(aux->dev),
		sizeof(aux->ddc.name));

	ret = drm_dp_aux_register_devnode(aux);
	if (ret)
		return ret;

	ret = i2c_add_adapter(&aux->ddc);
	if (ret) {
		drm_dp_aux_unregister_devnode(aux);
		return ret;
	}

	return 0;
}