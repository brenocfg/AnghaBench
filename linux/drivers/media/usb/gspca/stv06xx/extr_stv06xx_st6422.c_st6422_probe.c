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
struct TYPE_3__ {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct TYPE_4__ {TYPE_1__ cam; } ;
struct sd {scalar_t__ bridge; TYPE_2__ gspca_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ BRIDGE_ST6422 ; 
 int ENODEV ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  st6422_mode ; 

__attribute__((used)) static int st6422_probe(struct sd *sd)
{
	if (sd->bridge != BRIDGE_ST6422)
		return -ENODEV;

	pr_info("st6422 sensor detected\n");

	sd->gspca_dev.cam.cam_mode = st6422_mode;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(st6422_mode);
	return 0;
}