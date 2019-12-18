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
typedef  int /*<<< orphan*/  u32 ;
struct komeda_kms_dev {int dummy; } ;
struct komeda_component {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_PLANE_TYPE_OVERLAY ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 scalar_t__ KOMEDA_COMPONENT_LAYER0 ; 

__attribute__((used)) static u32 get_plane_type(struct komeda_kms_dev *kms,
			  struct komeda_component *c)
{
	bool is_primary = (c->id == KOMEDA_COMPONENT_LAYER0);

	return is_primary ? DRM_PLANE_TYPE_PRIMARY : DRM_PLANE_TYPE_OVERLAY;
}