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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 TYPE_2__* ov965x_formats ; 
 TYPE_1__* ov965x_framesizes ; 

__attribute__((used)) static void ov965x_get_default_format(struct v4l2_mbus_framefmt *mf)
{
	mf->width = ov965x_framesizes[0].width;
	mf->height = ov965x_framesizes[0].height;
	mf->colorspace = ov965x_formats[0].colorspace;
	mf->code = ov965x_formats[0].code;
	mf->field = V4L2_FIELD_NONE;
}