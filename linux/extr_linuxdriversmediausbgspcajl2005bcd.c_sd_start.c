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
struct sd {int /*<<< orphan*/  work_struct; int /*<<< orphan*/  cap_mode; } ;
struct TYPE_4__ {int width; } ;
struct TYPE_3__ {int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {TYPE_2__ pixfmt; TYPE_1__ cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jl2005c_stream_start_cif_lg (struct gspca_dev*) ; 
 int /*<<< orphan*/  jl2005c_stream_start_cif_small (struct gspca_dev*) ; 
 int /*<<< orphan*/  jl2005c_stream_start_vga_lg (struct gspca_dev*) ; 
 int /*<<< orphan*/  jl2005c_stream_start_vga_small (struct gspca_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{

	struct sd *sd = (struct sd *) gspca_dev;
	sd->cap_mode = gspca_dev->cam.cam_mode;

	switch (gspca_dev->pixfmt.width) {
	case 640:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at vga resolution\n");
		jl2005c_stream_start_vga_lg(gspca_dev);
		break;
	case 320:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at qvga resolution\n");
		jl2005c_stream_start_vga_small(gspca_dev);
		break;
	case 352:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at cif resolution\n");
		jl2005c_stream_start_cif_lg(gspca_dev);
		break;
	case 176:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at qcif resolution\n");
		jl2005c_stream_start_cif_small(gspca_dev);
		break;
	default:
		pr_err("Unknown resolution specified\n");
		return -1;
	}

	schedule_work(&sd->work_struct);

	return 0;
}