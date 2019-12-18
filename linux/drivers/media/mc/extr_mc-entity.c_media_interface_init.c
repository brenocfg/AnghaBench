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
struct media_interface {int /*<<< orphan*/  graph_obj; int /*<<< orphan*/  links; void* flags; void* type; } ;
struct media_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_gobj_create (struct media_device*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void media_interface_init(struct media_device *mdev,
				 struct media_interface *intf,
				 u32 gobj_type,
				 u32 intf_type, u32 flags)
{
	intf->type = intf_type;
	intf->flags = flags;
	INIT_LIST_HEAD(&intf->links);

	media_gobj_create(mdev, gobj_type, &intf->graph_obj);
}