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
struct nvkm_subdev {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mc_intr_unarm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_mc_fini(struct nvkm_subdev *subdev, bool suspend)
{
	nvkm_mc_intr_unarm(subdev->device);
	return 0;
}