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
struct firmware {int dummy; } ;

/* Variables and functions */
 int nvkm_firmware_get_version (struct nvkm_subdev const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct firmware const**) ; 

int
nvkm_firmware_get(const struct nvkm_subdev *subdev, const char *fwname,
		  const struct firmware **fw)
{
	return nvkm_firmware_get_version(subdev, fwname, 0, 0, fw);
}