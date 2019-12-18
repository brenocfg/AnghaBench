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
struct sunxi_engine {TYPE_1__* ops; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct drm_plane** (* layers_init ) (struct drm_device*,struct sunxi_engine*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 struct drm_plane** ERR_PTR (int /*<<< orphan*/ ) ; 
 struct drm_plane** stub1 (struct drm_device*,struct sunxi_engine*) ; 

__attribute__((used)) static inline struct drm_plane **
sunxi_engine_layers_init(struct drm_device *drm, struct sunxi_engine *engine)
{
	if (engine->ops && engine->ops->layers_init)
		return engine->ops->layers_init(drm, engine);
	return ERR_PTR(-ENOSYS);
}