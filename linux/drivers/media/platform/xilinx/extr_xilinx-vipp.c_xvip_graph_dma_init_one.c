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
struct xvip_dma {int /*<<< orphan*/  list; } ;
struct xvip_composite_device {int /*<<< orphan*/  v4l2_caps; int /*<<< orphan*/  dmas; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct device_node*) ; 
 struct xvip_dma* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int xvip_dma_init (struct xvip_composite_device*,struct xvip_dma*,int,unsigned int) ; 

__attribute__((used)) static int xvip_graph_dma_init_one(struct xvip_composite_device *xdev,
				   struct device_node *node)
{
	struct xvip_dma *dma;
	enum v4l2_buf_type type;
	const char *direction;
	unsigned int index;
	int ret;

	ret = of_property_read_string(node, "direction", &direction);
	if (ret < 0)
		return ret;

	if (strcmp(direction, "input") == 0)
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	else if (strcmp(direction, "output") == 0)
		type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	else
		return -EINVAL;

	of_property_read_u32(node, "reg", &index);

	dma = devm_kzalloc(xdev->dev, sizeof(*dma), GFP_KERNEL);
	if (dma == NULL)
		return -ENOMEM;

	ret = xvip_dma_init(xdev, dma, type, index);
	if (ret < 0) {
		dev_err(xdev->dev, "%pOF initialization failed\n", node);
		return ret;
	}

	list_add_tail(&dma->list, &xdev->dmas);

	xdev->v4l2_caps |= type == V4L2_BUF_TYPE_VIDEO_CAPTURE
			 ? V4L2_CAP_VIDEO_CAPTURE : V4L2_CAP_VIDEO_OUTPUT;

	return 0;
}