#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int sensor_flags; } ;
struct TYPE_4__ {int product; int device_type; } ;
struct TYPE_6__ {TYPE_2__ version; TYPE_1__ pnp_id; } ;
struct camera_data {int /*<<< orphan*/  dev; TYPE_3__ params; } ;

/* Variables and functions */
#define  CPIA2_VP_SENSOR_FLAGS_404 134 
#define  CPIA2_VP_SENSOR_FLAGS_407 133 
#define  CPIA2_VP_SENSOR_FLAGS_409 132 
#define  CPIA2_VP_SENSOR_FLAGS_410 131 
#define  CPIA2_VP_SENSOR_FLAGS_500 130 
#define  DEVICE_STV_672 129 
#define  DEVICE_STV_676 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_querycap(struct file *file, void *fh, struct v4l2_capability *vc)
{
	struct camera_data *cam = video_drvdata(file);

	strscpy(vc->driver, "cpia2", sizeof(vc->driver));

	if (cam->params.pnp_id.product == 0x151)
		strscpy(vc->card, "QX5 Microscope", sizeof(vc->card));
	else
		strscpy(vc->card, "CPiA2 Camera", sizeof(vc->card));
	switch (cam->params.pnp_id.device_type) {
	case DEVICE_STV_672:
		strcat(vc->card, " (672/");
		break;
	case DEVICE_STV_676:
		strcat(vc->card, " (676/");
		break;
	default:
		strcat(vc->card, " (XXX/");
		break;
	}
	switch (cam->params.version.sensor_flags) {
	case CPIA2_VP_SENSOR_FLAGS_404:
		strcat(vc->card, "404)");
		break;
	case CPIA2_VP_SENSOR_FLAGS_407:
		strcat(vc->card, "407)");
		break;
	case CPIA2_VP_SENSOR_FLAGS_409:
		strcat(vc->card, "409)");
		break;
	case CPIA2_VP_SENSOR_FLAGS_410:
		strcat(vc->card, "410)");
		break;
	case CPIA2_VP_SENSOR_FLAGS_500:
		strcat(vc->card, "500)");
		break;
	default:
		strcat(vc->card, "XXX)");
		break;
	}

	if (usb_make_path(cam->dev, vc->bus_info, sizeof(vc->bus_info)) <0)
		memset(vc->bus_info,0, sizeof(vc->bus_info));
	return 0;
}