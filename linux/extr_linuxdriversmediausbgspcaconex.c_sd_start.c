#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {int /*<<< orphan*/  jpeg_hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct gspca_dev {TYPE_1__ pixfmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUALITY ; 
 int /*<<< orphan*/  cx11646_fw (struct gspca_dev*) ; 
 int /*<<< orphan*/  cx11646_initsize (struct gspca_dev*) ; 
 int /*<<< orphan*/  cx11646_jpeg (struct gspca_dev*) ; 
 int /*<<< orphan*/  cx_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  jpeg_define (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x22);		/* JPEG 411 */
	jpeg_set_qual(sd->jpeg_hdr, QUALITY);

	cx11646_initsize(gspca_dev);
	cx11646_fw(gspca_dev);
	cx_sensor(gspca_dev);
	cx11646_jpeg(gspca_dev);
	return 0;
}