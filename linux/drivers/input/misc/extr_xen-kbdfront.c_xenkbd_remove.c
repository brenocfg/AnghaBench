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
struct xenkbd_info {scalar_t__ page; scalar_t__ mtouch; scalar_t__ ptr; scalar_t__ kbd; } ;
struct xenbus_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct xenkbd_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct xenkbd_info*) ; 
 int /*<<< orphan*/  xenkbd_disconnect_backend (struct xenkbd_info*) ; 

__attribute__((used)) static int xenkbd_remove(struct xenbus_device *dev)
{
	struct xenkbd_info *info = dev_get_drvdata(&dev->dev);

	xenkbd_disconnect_backend(info);
	if (info->kbd)
		input_unregister_device(info->kbd);
	if (info->ptr)
		input_unregister_device(info->ptr);
	if (info->mtouch)
		input_unregister_device(info->mtouch);
	free_page((unsigned long)info->page);
	kfree(info);
	return 0;
}