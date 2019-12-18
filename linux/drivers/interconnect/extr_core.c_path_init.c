#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct icc_path {int num_nodes; TYPE_2__* reqs; } ;
struct icc_node {struct icc_node* reverse; int /*<<< orphan*/  req_list; TYPE_1__* provider; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {struct device* dev; struct icc_node* node; int /*<<< orphan*/  req_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct icc_path* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct icc_path* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reqs ; 
 int /*<<< orphan*/  struct_size (struct icc_path*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct icc_path *path_init(struct device *dev, struct icc_node *dst,
				  ssize_t num_nodes)
{
	struct icc_node *node = dst;
	struct icc_path *path;
	int i;

	path = kzalloc(struct_size(path, reqs, num_nodes), GFP_KERNEL);
	if (!path)
		return ERR_PTR(-ENOMEM);

	path->num_nodes = num_nodes;

	for (i = num_nodes - 1; i >= 0; i--) {
		node->provider->users++;
		hlist_add_head(&path->reqs[i].req_node, &node->req_list);
		path->reqs[i].node = node;
		path->reqs[i].dev = dev;
		/* reference to previous node was saved during path traversal */
		node = node->reverse;
	}

	return path;
}