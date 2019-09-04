#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_async_notifier {size_t num_subdevs; TYPE_3__** subdevs; } ;
struct TYPE_6__ {struct fwnode_handle* fwnode; } ;
struct TYPE_8__ {int /*<<< orphan*/  match_type; TYPE_1__ match; } ;
struct TYPE_7__ {TYPE_3__ asd; } ;
struct rcar_drif_sdr {TYPE_2__ ep; TYPE_4__* dev; struct v4l2_async_notifier notifier; } ;
struct fwnode_handle {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 int /*<<< orphan*/  dev_warn (TYPE_4__*,char*) ; 
 TYPE_3__** devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 struct fwnode_handle* fwnode_graph_get_next_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fwnode_handle* fwnode_graph_get_remote_port_parent (struct fwnode_handle*) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int /*<<< orphan*/  of_fwnode_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_drif_get_ep_properties (struct rcar_drif_sdr*,struct fwnode_handle*) ; 

__attribute__((used)) static int rcar_drif_parse_subdevs(struct rcar_drif_sdr *sdr)
{
	struct v4l2_async_notifier *notifier = &sdr->notifier;
	struct fwnode_handle *fwnode, *ep;

	notifier->subdevs = devm_kzalloc(sdr->dev, sizeof(*notifier->subdevs),
					 GFP_KERNEL);
	if (!notifier->subdevs)
		return -ENOMEM;

	ep = fwnode_graph_get_next_endpoint(of_fwnode_handle(sdr->dev->of_node),
					    NULL);
	if (!ep)
		return 0;

	notifier->subdevs[notifier->num_subdevs] = &sdr->ep.asd;
	fwnode = fwnode_graph_get_remote_port_parent(ep);
	if (!fwnode) {
		dev_warn(sdr->dev, "bad remote port parent\n");
		fwnode_handle_put(ep);
		return -EINVAL;
	}

	sdr->ep.asd.match.fwnode = fwnode;
	sdr->ep.asd.match_type = V4L2_ASYNC_MATCH_FWNODE;
	notifier->num_subdevs++;

	/* Get the endpoint properties */
	rcar_drif_get_ep_properties(sdr, ep);

	fwnode_handle_put(fwnode);
	fwnode_handle_put(ep);

	return 0;
}