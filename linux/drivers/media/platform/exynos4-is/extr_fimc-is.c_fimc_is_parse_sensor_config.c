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
typedef  scalar_t__ u32 ;
struct fimc_is_sensor {scalar_t__ i2c_bus; int /*<<< orphan*/  drvdata; } ;
struct fimc_is {TYPE_1__* pdev; struct fimc_is_sensor* sensor; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ FIMC_INPUT_MIPI_CSI2_0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,struct device_node*) ; 
 int /*<<< orphan*/  fimc_is_sensor_get_drvdata (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,int /*<<< orphan*/ *) ; 
 struct device_node* of_graph_get_remote_port (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

__attribute__((used)) static int fimc_is_parse_sensor_config(struct fimc_is *is, unsigned int index,
						struct device_node *node)
{
	struct fimc_is_sensor *sensor = &is->sensor[index];
	struct device_node *ep, *port;
	u32 tmp = 0;
	int ret;

	sensor->drvdata = fimc_is_sensor_get_drvdata(node);
	if (!sensor->drvdata) {
		dev_err(&is->pdev->dev, "no driver data found for: %pOF\n",
							 node);
		return -EINVAL;
	}

	ep = of_graph_get_next_endpoint(node, NULL);
	if (!ep)
		return -ENXIO;

	port = of_graph_get_remote_port(ep);
	of_node_put(ep);
	if (!port)
		return -ENXIO;

	/* Use MIPI-CSIS channel id to determine the ISP I2C bus index. */
	ret = of_property_read_u32(port, "reg", &tmp);
	if (ret < 0) {
		dev_err(&is->pdev->dev, "reg property not found at: %pOF\n",
							 port);
		of_node_put(port);
		return ret;
	}

	of_node_put(port);
	sensor->i2c_bus = tmp - FIMC_INPUT_MIPI_CSI2_0;
	return 0;
}