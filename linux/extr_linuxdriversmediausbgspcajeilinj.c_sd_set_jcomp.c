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
struct v4l2_jpegcompression {int /*<<< orphan*/  quality; } ;
struct sd {int /*<<< orphan*/  jpegqual; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_s_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_set_jcomp(struct gspca_dev *gspca_dev,
			const struct v4l2_jpegcompression *jcomp)
{
	struct sd *sd = (struct sd *) gspca_dev;

	v4l2_ctrl_s_ctrl(sd->jpegqual, jcomp->quality);
	return 0;
}