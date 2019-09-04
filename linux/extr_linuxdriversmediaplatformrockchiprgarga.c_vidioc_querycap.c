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
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;

/* Variables and functions */
 char* RGA_NAME ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
vidioc_querycap(struct file *file, void *priv, struct v4l2_capability *cap)
{
	strlcpy(cap->driver, RGA_NAME, sizeof(cap->driver));
	strlcpy(cap->card, "rockchip-rga", sizeof(cap->card));
	strlcpy(cap->bus_info, "platform:rga", sizeof(cap->bus_info));

	return 0;
}