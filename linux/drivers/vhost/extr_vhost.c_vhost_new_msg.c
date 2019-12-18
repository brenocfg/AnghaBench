#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vhost_virtqueue {int dummy; } ;
struct TYPE_2__ {int type; } ;
struct vhost_msg_node {TYPE_1__ msg; struct vhost_virtqueue* vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vhost_msg_node* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

struct vhost_msg_node *vhost_new_msg(struct vhost_virtqueue *vq, int type)
{
	struct vhost_msg_node *node = kmalloc(sizeof *node, GFP_KERNEL);
	if (!node)
		return NULL;

	/* Make sure all padding within the structure is initialized. */
	memset(&node->msg, 0, sizeof node->msg);
	node->vq = vq;
	node->msg.type = type;
	return node;
}