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
struct rcar_du_device {int /*<<< orphan*/  dev; } ;
struct of_endpoint {struct device_node* local_node; } ;
struct device_node {int dummy; } ;
typedef  enum rcar_du_output { ____Placeholder_rcar_du_output } rcar_du_output ;

/* Variables and functions */
 int ENODEV ; 
 int ENOLINK ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct device_node*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,struct device_node*,int,int) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int rcar_du_encoder_init (struct rcar_du_device*,int,struct device_node*) ; 

__attribute__((used)) static int rcar_du_encoders_init_one(struct rcar_du_device *rcdu,
				     enum rcar_du_output output,
				     struct of_endpoint *ep)
{
	struct device_node *entity;
	int ret;

	/* Locate the connected entity and initialize the encoder. */
	entity = of_graph_get_remote_port_parent(ep->local_node);
	if (!entity) {
		dev_dbg(rcdu->dev, "unconnected endpoint %pOF, skipping\n",
			ep->local_node);
		return -ENODEV;
	}

	if (!of_device_is_available(entity)) {
		dev_dbg(rcdu->dev,
			"connected entity %pOF is disabled, skipping\n",
			entity);
		of_node_put(entity);
		return -ENODEV;
	}

	ret = rcar_du_encoder_init(rcdu, output, entity);
	if (ret && ret != -EPROBE_DEFER && ret != -ENOLINK)
		dev_warn(rcdu->dev,
			 "failed to initialize encoder %pOF on output %u (%d), skipping\n",
			 entity, output, ret);

	of_node_put(entity);

	return ret;
}