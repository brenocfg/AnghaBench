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
struct pxa_camera_format_xlate {int dummy; } ;
struct pxa_camera_dev {struct pxa_camera_format_xlate* user_formats; int /*<<< orphan*/  sensor; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct pxa_camera_format_xlate*) ; 
 int PTR_ERR (struct pxa_camera_format_xlate*) ; 
 int /*<<< orphan*/  pxa_camera_get_formats ; 
 struct pxa_camera_format_xlate* pxa_mbus_build_fmts_xlate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa_camera_build_formats(struct pxa_camera_dev *pcdev)
{
	struct pxa_camera_format_xlate *xlate;

	xlate = pxa_mbus_build_fmts_xlate(&pcdev->v4l2_dev, pcdev->sensor,
					  pxa_camera_get_formats);
	if (IS_ERR(xlate))
		return PTR_ERR(xlate);

	pcdev->user_formats = xlate;
	return 0;
}