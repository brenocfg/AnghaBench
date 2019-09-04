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
typedef  int u32 ;
struct vc4_dev {int /*<<< orphan*/  firmware; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_plane {int /*<<< orphan*/  name; TYPE_1__ base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RPI_FIRMWARE_FRAMEBUFFER_BLANK ; 
 int rpi_firmware_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc4_plane_set_primary_blank(struct drm_plane *plane, bool blank)
{
	struct vc4_dev *vc4 = to_vc4_dev(plane->dev);

	u32 packet = blank;

	DRM_DEBUG_ATOMIC("[PLANE:%d:%s] primary plane %s",
			 plane->base.id, plane->name,
			 blank ? "blank" : "unblank");

	return rpi_firmware_property(vc4->firmware,
				     RPI_FIRMWARE_FRAMEBUFFER_BLANK,
				     &packet, sizeof(packet));
}