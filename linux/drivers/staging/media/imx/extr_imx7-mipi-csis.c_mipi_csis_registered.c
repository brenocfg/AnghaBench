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
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  entity; } ;
struct csi_state {TYPE_2__* pads; TYPE_1__ mipi_sd; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIS_PADS_NUM ; 
 size_t CSIS_PAD_SINK ; 
 size_t CSIS_PAD_SOURCE ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct csi_state* mipi_sd_to_csis_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int mipi_csis_registered(struct v4l2_subdev *mipi_sd)
{
	struct csi_state *state = mipi_sd_to_csis_state(mipi_sd);

	state->pads[CSIS_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	state->pads[CSIS_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	return media_entity_pads_init(&state->mipi_sd.entity, CSIS_PADS_NUM,
				      state->pads);
}