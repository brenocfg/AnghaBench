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
struct nvkm_subdev {int dummy; } ;
struct nvkm_iccsense_sensor {int /*<<< orphan*/  config; int /*<<< orphan*/  addr; int /*<<< orphan*/  i2c; int /*<<< orphan*/  id; } ;
struct nvkm_iccsense {struct nvkm_subdev subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wr16i2cr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_trace (struct nvkm_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvkm_iccsense_sensor_config(struct nvkm_iccsense *iccsense,
		            struct nvkm_iccsense_sensor *sensor)
{
	struct nvkm_subdev *subdev = &iccsense->subdev;
	nvkm_trace(subdev, "write config of extdev %i: 0x%04x\n", sensor->id, sensor->config);
	nv_wr16i2cr(sensor->i2c, sensor->addr, 0x00, sensor->config);
}