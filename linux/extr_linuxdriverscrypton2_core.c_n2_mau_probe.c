#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct n2_mau {int /*<<< orphan*/  mau_list; int /*<<< orphan*/  mau_info; } ;
struct mdesc_handle {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HV_NCS_QTYPE_MAU ; 
 struct n2_mau* alloc_ncp () ; 
 int /*<<< orphan*/  cpu_to_mau ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct n2_mau*) ; 
 int /*<<< orphan*/  free_ncp (struct n2_mau*) ; 
 int grab_global_resources () ; 
 int grab_mdesc_irq_props (struct mdesc_handle*,struct platform_device*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mau_intr ; 
 struct mdesc_handle* mdesc_grab () ; 
 int /*<<< orphan*/  mdesc_release (struct mdesc_handle*) ; 
 int /*<<< orphan*/  n2_spu_driver_version () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_global_resources () ; 
 int spu_mdesc_scan (struct mdesc_handle*,struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int n2_mau_probe(struct platform_device *dev)
{
	struct mdesc_handle *mdesc;
	struct n2_mau *mp;
	int err;

	n2_spu_driver_version();

	pr_info("Found NCP at %pOF\n", dev->dev.of_node);

	mp = alloc_ncp();
	if (!mp) {
		dev_err(&dev->dev, "%pOF: Unable to allocate ncp.\n",
			dev->dev.of_node);
		return -ENOMEM;
	}

	err = grab_global_resources();
	if (err) {
		dev_err(&dev->dev, "%pOF: Unable to grab global resources.\n",
			dev->dev.of_node);
		goto out_free_ncp;
	}

	mdesc = mdesc_grab();

	if (!mdesc) {
		dev_err(&dev->dev, "%pOF: Unable to grab MDESC.\n",
			dev->dev.of_node);
		err = -ENODEV;
		goto out_free_global;
	}

	err = grab_mdesc_irq_props(mdesc, dev, &mp->mau_info, "ncp");
	if (err) {
		dev_err(&dev->dev, "%pOF: Unable to grab IRQ props.\n",
			dev->dev.of_node);
		mdesc_release(mdesc);
		goto out_free_global;
	}

	err = spu_mdesc_scan(mdesc, dev, &mp->mau_info, &mp->mau_list,
			     "mau", HV_NCS_QTYPE_MAU, mau_intr,
			     cpu_to_mau);
	mdesc_release(mdesc);

	if (err) {
		dev_err(&dev->dev, "%pOF: MAU MDESC scan failed.\n",
			dev->dev.of_node);
		goto out_free_global;
	}

	dev_set_drvdata(&dev->dev, mp);

	return 0;

out_free_global:
	release_global_resources();

out_free_ncp:
	free_ncp(mp);

	return err;
}