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
typedef  int /*<<< orphan*/  u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dss_device {int dummy; } ;
struct dpi_data {int dss_model; int /*<<< orphan*/  lock; struct dss_device* dss; struct platform_device* pdev; int /*<<< orphan*/  data_lines; } ;
struct device_node {struct dpi_data* data; } ;
typedef  enum dss_model { ____Placeholder_dss_model } dss_model ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dpi_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dpi_init_output_port (struct dpi_data*,struct device_node*) ; 
 int dpi_init_regulator (struct dpi_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

int dpi_init_port(struct dss_device *dss, struct platform_device *pdev,
		  struct device_node *port, enum dss_model dss_model)
{
	struct dpi_data *dpi;
	struct device_node *ep;
	u32 datalines;
	int r;

	dpi = devm_kzalloc(&pdev->dev, sizeof(*dpi), GFP_KERNEL);
	if (!dpi)
		return -ENOMEM;

	ep = of_get_next_child(port, NULL);
	if (!ep)
		return 0;

	r = of_property_read_u32(ep, "data-lines", &datalines);
	of_node_put(ep);
	if (r) {
		DSSERR("failed to parse datalines\n");
		return r;
	}

	dpi->data_lines = datalines;

	dpi->pdev = pdev;
	dpi->dss_model = dss_model;
	dpi->dss = dss;
	port->data = dpi;

	mutex_init(&dpi->lock);

	r = dpi_init_regulator(dpi);
	if (r)
		return r;

	return dpi_init_output_port(dpi, port);
}