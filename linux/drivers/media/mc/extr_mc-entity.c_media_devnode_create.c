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
typedef  void* u32 ;
struct media_intf_devnode {int /*<<< orphan*/  intf; void* minor; void* major; } ;
struct media_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_GRAPH_INTF_DEVNODE ; 
 struct media_intf_devnode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_interface_init (struct media_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,void*) ; 

struct media_intf_devnode *media_devnode_create(struct media_device *mdev,
						u32 type, u32 flags,
						u32 major, u32 minor)
{
	struct media_intf_devnode *devnode;

	devnode = kzalloc(sizeof(*devnode), GFP_KERNEL);
	if (!devnode)
		return NULL;

	devnode->major = major;
	devnode->minor = minor;

	media_interface_init(mdev, &devnode->intf, MEDIA_GRAPH_INTF_DEVNODE,
			     type, flags);

	return devnode;
}