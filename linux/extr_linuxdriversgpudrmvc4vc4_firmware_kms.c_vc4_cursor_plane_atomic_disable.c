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
struct drm_plane_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_plane {int /*<<< orphan*/  name; TYPE_1__ base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  packet_state ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  RPI_FIRMWARE_SET_CURSOR_STATE ; 
 int rpi_firmware_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**,int) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_cursor_plane_atomic_disable(struct drm_plane *plane,
					    struct drm_plane_state *old_state)
{
	struct vc4_dev *vc4 = to_vc4_dev(plane->dev);
	u32 packet_state[] = { false, 0, 0, 0 };
	int ret;

	DRM_DEBUG_ATOMIC("[PLANE:%d:%s] disabling cursor", plane->base.id, plane->name);

	ret = rpi_firmware_property(vc4->firmware,
				    RPI_FIRMWARE_SET_CURSOR_STATE,
				    &packet_state,
				    sizeof(packet_state));
	if (ret || packet_state[0] != 0)
		DRM_ERROR("Failed to set cursor state: 0x%08x\n", packet_state[0]);
}