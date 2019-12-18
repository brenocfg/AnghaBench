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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_FIXED ; 
 int /*<<< orphan*/  S5K5BAF_CIS_HEIGHT ; 
 int /*<<< orphan*/  S5K5BAF_CIS_WIDTH ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 

__attribute__((used)) static void s5k5baf_try_cis_format(struct v4l2_mbus_framefmt *mf)
{
	mf->width = S5K5BAF_CIS_WIDTH;
	mf->height = S5K5BAF_CIS_HEIGHT;
	mf->code = MEDIA_BUS_FMT_FIXED;
	mf->colorspace = V4L2_COLORSPACE_JPEG;
	mf->field = V4L2_FIELD_NONE;
}