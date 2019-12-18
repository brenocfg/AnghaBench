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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct komeda_plane {TYPE_2__* layer; } ;
struct komeda_dev {int /*<<< orphan*/  fmt_tbl; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  layer_type; } ;
struct TYPE_3__ {struct komeda_dev* dev_private; } ;

/* Variables and functions */
 int komeda_format_mod_supported (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct komeda_plane* to_kplane (struct drm_plane*) ; 

__attribute__((used)) static bool
komeda_plane_format_mod_supported(struct drm_plane *plane,
				  u32 format, u64 modifier)
{
	struct komeda_dev *mdev = plane->dev->dev_private;
	struct komeda_plane *kplane = to_kplane(plane);
	u32 layer_type = kplane->layer->layer_type;

	return komeda_format_mod_supported(&mdev->fmt_tbl, layer_type,
					   format, modifier, 0);
}