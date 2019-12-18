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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mi1320_camera_settings (struct gspca_dev*) ; 

__attribute__((used)) static int mi1320_init_post_alt(struct gspca_dev *gspca_dev)
{
	mi1320_camera_settings(gspca_dev);

	return 0;
}