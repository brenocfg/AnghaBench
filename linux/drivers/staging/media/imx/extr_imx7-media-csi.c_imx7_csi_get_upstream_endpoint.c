#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct media_entity {scalar_t__ function; } ;
struct v4l2_subdev {TYPE_3__* dev; struct media_entity entity; } ;
struct v4l2_fwnode_endpoint {int dummy; } ;
struct media_pad {int /*<<< orphan*/  index; int /*<<< orphan*/  entity; } ;
struct TYPE_5__ {struct media_entity entity; } ;
struct imx7_csi {TYPE_2__ sd; TYPE_1__* src_sd; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {struct media_entity entity; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPIPE ; 
 scalar_t__ MEDIA_ENT_F_VID_IF_BRIDGE ; 
 scalar_t__ MEDIA_ENT_F_VID_MUX ; 
 struct media_pad* imx_media_pipeline_pad (struct media_entity*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 struct device_node* of_graph_get_port_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int imx7_csi_get_upstream_endpoint(struct imx7_csi *csi,
					  struct v4l2_fwnode_endpoint *ep,
					  bool skip_mux)
{
	struct device_node *endpoint, *port;
	struct media_entity *src;
	struct v4l2_subdev *sd;
	struct media_pad *pad;

	if (!csi->src_sd)
		return -EPIPE;

	src = &csi->src_sd->entity;

	/*
	 * if the source is neither a mux or csi2 get the one directly upstream
	 * from this csi
	 */
	if (src->function != MEDIA_ENT_F_VID_IF_BRIDGE &&
	    src->function != MEDIA_ENT_F_VID_MUX)
		src = &csi->sd.entity;

skip_video_mux:
	/* get source pad of entity directly upstream from src */
	pad = imx_media_pipeline_pad(src, 0, 0, true);
	if (!pad)
		return -ENODEV;

	sd = media_entity_to_v4l2_subdev(pad->entity);

	/* To get bus type we may need to skip video mux */
	if (skip_mux && src->function == MEDIA_ENT_F_VID_MUX) {
		src = &sd->entity;
		goto skip_video_mux;
	}

	/*
	 * NOTE: this assumes an OF-graph port id is the same as a
	 * media pad index.
	 */
	port = of_graph_get_port_by_id(sd->dev->of_node, pad->index);
	if (!port)
		return -ENODEV;

	endpoint = of_get_next_child(port, NULL);
	of_node_put(port);
	if (!endpoint)
		return -ENODEV;

	v4l2_fwnode_endpoint_parse(of_fwnode_handle(endpoint), ep);
	of_node_put(endpoint);

	return 0;
}