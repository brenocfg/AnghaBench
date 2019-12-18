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
struct rio_net {int /*<<< orphan*/  mports; int /*<<< orphan*/  switches; int /*<<< orphan*/  devices; int /*<<< orphan*/  node; } ;
struct rio_mport {struct rio_net* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct rio_net* kzalloc (int,int /*<<< orphan*/ ) ; 

struct rio_net *rio_alloc_net(struct rio_mport *mport)
{
	struct rio_net *net = kzalloc(sizeof(*net), GFP_KERNEL);

	if (net) {
		INIT_LIST_HEAD(&net->node);
		INIT_LIST_HEAD(&net->devices);
		INIT_LIST_HEAD(&net->switches);
		INIT_LIST_HEAD(&net->mports);
		mport->net = net;
	}
	return net;
}