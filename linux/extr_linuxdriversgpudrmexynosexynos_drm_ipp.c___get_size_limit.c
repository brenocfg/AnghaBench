#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  align; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_5__ {int /*<<< orphan*/  align; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct drm_ipp_limit {TYPE_3__ v; TYPE_1__ h; } ;
struct TYPE_8__ {int /*<<< orphan*/  align; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_6__ {int /*<<< orphan*/  align; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct drm_exynos_ipp_limit {int type; TYPE_4__ v; TYPE_2__ h; } ;
typedef  enum drm_ipp_size_id { ____Placeholder_drm_ipp_size_id } drm_ipp_size_id ;

/* Variables and functions */
 int DRM_EXYNOS_IPP_LIMIT_SIZE_MASK ; 
 int DRM_EXYNOS_IPP_LIMIT_TYPE_MASK ; 
 int DRM_EXYNOS_IPP_LIMIT_TYPE_SIZE ; 
 int /*<<< orphan*/  __limit_set_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int** limit_id_fallback ; 
 int /*<<< orphan*/  memset (struct drm_ipp_limit*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __get_size_limit(const struct drm_exynos_ipp_limit *limits,
			     unsigned int num_limits, enum drm_ipp_size_id id,
			     struct drm_ipp_limit *res)
{
	const struct drm_exynos_ipp_limit *l = limits;
	int i = 0;

	memset(res, 0, sizeof(*res));
	for (i = 0; limit_id_fallback[id][i]; i++)
		for (l = limits; l - limits < num_limits; l++) {
			if (((l->type & DRM_EXYNOS_IPP_LIMIT_TYPE_MASK) !=
			      DRM_EXYNOS_IPP_LIMIT_TYPE_SIZE) ||
			    ((l->type & DRM_EXYNOS_IPP_LIMIT_SIZE_MASK) !=
						     limit_id_fallback[id][i]))
				continue;
			__limit_set_val(&res->h.min, l->h.min);
			__limit_set_val(&res->h.max, l->h.max);
			__limit_set_val(&res->h.align, l->h.align);
			__limit_set_val(&res->v.min, l->v.min);
			__limit_set_val(&res->v.max, l->v.max);
			__limit_set_val(&res->v.align, l->v.align);
		}
}