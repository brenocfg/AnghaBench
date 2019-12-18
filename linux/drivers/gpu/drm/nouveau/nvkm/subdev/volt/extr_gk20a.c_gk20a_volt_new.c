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
struct nvkm_volt {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct gk20a_volt {struct nvkm_volt base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gk20a_cvb_coef ; 
 int gk20a_volt_ctor (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gk20a_volt*) ; 
 struct gk20a_volt* kzalloc (int,int /*<<< orphan*/ ) ; 

int
gk20a_volt_new(struct nvkm_device *device, int index, struct nvkm_volt **pvolt)
{
	struct gk20a_volt *volt;

	volt = kzalloc(sizeof(*volt), GFP_KERNEL);
	if (!volt)
		return -ENOMEM;
	*pvolt = &volt->base;

	return gk20a_volt_ctor(device, index, gk20a_cvb_coef,
			       ARRAY_SIZE(gk20a_cvb_coef), 0, volt);
}