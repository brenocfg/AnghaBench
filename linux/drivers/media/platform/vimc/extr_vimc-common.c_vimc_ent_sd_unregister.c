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
struct vimc_ent_device {int /*<<< orphan*/  pads; int /*<<< orphan*/  ent; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  vimc_pads_cleanup (int /*<<< orphan*/ ) ; 

void vimc_ent_sd_unregister(struct vimc_ent_device *ved, struct v4l2_subdev *sd)
{
	media_entity_cleanup(ved->ent);
	vimc_pads_cleanup(ved->pads);
	v4l2_device_unregister_subdev(sd);
}