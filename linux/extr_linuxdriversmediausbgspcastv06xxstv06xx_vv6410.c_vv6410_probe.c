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
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct TYPE_4__ {TYPE_1__ cam; } ;
struct sd {TYPE_2__ gspca_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  VV6410_DEVICEH ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int stv06xx_read_sensor (struct sd*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vv6410_mode ; 

__attribute__((used)) static int vv6410_probe(struct sd *sd)
{
	u16 data;
	int err;

	err = stv06xx_read_sensor(sd, VV6410_DEVICEH, &data);
	if (err < 0)
		return -ENODEV;

	if (data != 0x19)
		return -ENODEV;

	pr_info("vv6410 sensor detected\n");

	sd->gspca_dev.cam.cam_mode = vv6410_mode;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(vv6410_mode);
	return 0;
}