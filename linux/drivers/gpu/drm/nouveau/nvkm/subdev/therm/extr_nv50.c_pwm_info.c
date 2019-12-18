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
struct nvkm_therm {struct nvkm_subdev subdev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 

__attribute__((used)) static int
pwm_info(struct nvkm_therm *therm, int *line, int *ctrl, int *indx)
{
	struct nvkm_subdev *subdev = &therm->subdev;

	if (*line == 0x04) {
		*ctrl = 0x00e100;
		*line = 4;
		*indx = 0;
	} else
	if (*line == 0x09) {
		*ctrl = 0x00e100;
		*line = 9;
		*indx = 1;
	} else
	if (*line == 0x10) {
		*ctrl = 0x00e28c;
		*line = 0;
		*indx = 0;
	} else {
		nvkm_error(subdev, "unknown pwm ctrl for gpio %d\n", *line);
		return -ENODEV;
	}

	return 0;
}