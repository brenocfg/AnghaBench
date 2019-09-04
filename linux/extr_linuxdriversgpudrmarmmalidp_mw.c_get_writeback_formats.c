#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct malidp_hw_regmap {int n_pixel_formats; TYPE_1__* pixel_formats; } ;
struct malidp_drm {TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__* hw; } ;
struct TYPE_5__ {struct malidp_hw_regmap map; } ;
struct TYPE_4__ {int layer; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SE_MEMWRITE ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 *get_writeback_formats(struct malidp_drm *malidp, int *n_formats)
{
	const struct malidp_hw_regmap *map = &malidp->dev->hw->map;
	u32 *formats;
	int n, i;

	formats = kcalloc(map->n_pixel_formats, sizeof(*formats),
			  GFP_KERNEL);
	if (!formats)
		return NULL;

	for (n = 0, i = 0;  i < map->n_pixel_formats; i++) {
		if (map->pixel_formats[i].layer & SE_MEMWRITE)
			formats[n++] = map->pixel_formats[i].format;
	}

	*n_formats = n;

	return formats;
}