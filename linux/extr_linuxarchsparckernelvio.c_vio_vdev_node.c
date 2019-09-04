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
typedef  int /*<<< orphan*/  u64 ;
struct vio_dev {int /*<<< orphan*/  md_node_info; scalar_t__ node_name; } ;
struct mdesc_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDESC_NODE_NULL ; 
 int /*<<< orphan*/  mdesc_get_node (struct mdesc_handle*,char const*,int /*<<< orphan*/ *) ; 

u64 vio_vdev_node(struct mdesc_handle *hp, struct vio_dev *vdev)
{
	u64 node;

	if (vdev == NULL)
		return MDESC_NODE_NULL;

	node = mdesc_get_node(hp, (const char *)vdev->node_name,
			      &vdev->md_node_info);

	return node;
}