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
struct xenkbd_info {int /*<<< orphan*/  page; } ;
struct xenbus_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct xenkbd_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xenkbd_connect_backend (struct xenbus_device*,struct xenkbd_info*) ; 
 int /*<<< orphan*/  xenkbd_disconnect_backend (struct xenkbd_info*) ; 

__attribute__((used)) static int xenkbd_resume(struct xenbus_device *dev)
{
	struct xenkbd_info *info = dev_get_drvdata(&dev->dev);

	xenkbd_disconnect_backend(info);
	memset(info->page, 0, PAGE_SIZE);
	return xenkbd_connect_backend(dev, info);
}