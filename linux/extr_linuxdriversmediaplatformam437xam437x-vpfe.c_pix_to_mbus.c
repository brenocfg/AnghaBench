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
struct vpfe_fmt {int /*<<< orphan*/  code; } ;
struct vpfe_device {int dummy; } ;
struct v4l2_pix_format {int /*<<< orphan*/  pixelformat; } ;
struct v4l2_mbus_framefmt {int dummy; } ;

/* Variables and functions */
 struct vpfe_fmt* find_format_by_pix (int /*<<< orphan*/ ) ; 
 struct vpfe_fmt* formats ; 
 int /*<<< orphan*/  memset (struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (struct v4l2_mbus_framefmt*,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpfe_dbg (int,struct vpfe_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pix_to_mbus(struct vpfe_device *vpfe,
			struct v4l2_pix_format *pix_fmt,
			struct v4l2_mbus_framefmt *mbus_fmt)
{
	struct vpfe_fmt *fmt;

	fmt = find_format_by_pix(pix_fmt->pixelformat);
	if (!fmt) {
		/* default to first entry */
		vpfe_dbg(3, vpfe, "Invalid pixel code: %x, default used instead\n",
			pix_fmt->pixelformat);
		fmt = &formats[0];
	}

	memset(mbus_fmt, 0, sizeof(*mbus_fmt));
	v4l2_fill_mbus_format(mbus_fmt, pix_fmt, fmt->code);
}