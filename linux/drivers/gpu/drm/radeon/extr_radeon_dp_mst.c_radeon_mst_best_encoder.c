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
struct radeon_connector {TYPE_1__* mst_encoder; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {struct drm_encoder base; } ;

/* Variables and functions */
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

__attribute__((used)) static struct
drm_encoder *radeon_mst_best_encoder(struct drm_connector *connector)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);

	return &radeon_connector->mst_encoder->base;
}