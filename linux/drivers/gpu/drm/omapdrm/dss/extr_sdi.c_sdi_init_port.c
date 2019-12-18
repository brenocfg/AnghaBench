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
struct sdi_device {int /*<<< orphan*/  vdds_sdi_reg; struct platform_device* pdev; struct dss_device* dss; int /*<<< orphan*/  datapairs; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dss_device {int dummy; } ;
struct device_node {struct sdi_device* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct sdi_device*) ; 
 struct sdi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int sdi_init_output (struct sdi_device*) ; 

int sdi_init_port(struct dss_device *dss, struct platform_device *pdev,
		  struct device_node *port)
{
	struct sdi_device *sdi;
	struct device_node *ep;
	u32 datapairs;
	int r;

	sdi = kzalloc(sizeof(*sdi), GFP_KERNEL);
	if (!sdi)
		return -ENOMEM;

	ep = of_get_next_child(port, NULL);
	if (!ep) {
		r = 0;
		goto err_free;
	}

	r = of_property_read_u32(ep, "datapairs", &datapairs);
	of_node_put(ep);
	if (r) {
		DSSERR("failed to parse datapairs\n");
		goto err_free;
	}

	sdi->datapairs = datapairs;
	sdi->dss = dss;

	sdi->pdev = pdev;
	port->data = sdi;

	sdi->vdds_sdi_reg = devm_regulator_get(&pdev->dev, "vdds_sdi");
	if (IS_ERR(sdi->vdds_sdi_reg)) {
		r = PTR_ERR(sdi->vdds_sdi_reg);
		if (r != -EPROBE_DEFER)
			DSSERR("can't get VDDS_SDI regulator\n");
		goto err_free;
	}

	r = sdi_init_output(sdi);
	if (r)
		goto err_free;

	return 0;

err_free:
	kfree(sdi);

	return r;
}