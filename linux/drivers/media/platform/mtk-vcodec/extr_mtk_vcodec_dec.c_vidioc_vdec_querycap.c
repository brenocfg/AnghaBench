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
struct v4l2_capability {int /*<<< orphan*/  card; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_PLATFORM_STR ; 
 int /*<<< orphan*/  MTK_VCODEC_DEC_NAME ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_vdec_querycap(struct file *file, void *priv,
				struct v4l2_capability *cap)
{
	strscpy(cap->driver, MTK_VCODEC_DEC_NAME, sizeof(cap->driver));
	strscpy(cap->bus_info, MTK_PLATFORM_STR, sizeof(cap->bus_info));
	strscpy(cap->card, MTK_PLATFORM_STR, sizeof(cap->card));

	return 0;
}