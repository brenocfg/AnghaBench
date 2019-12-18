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
typedef  int u32 ;
struct soc_device_attribute {char* family; void* soc_id; void* revision; int /*<<< orphan*/  machine; } ;
struct soc_device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct soc_device*) ; 
 int PTR_ERR (struct soc_device*) ; 
 int /*<<< orphan*/  dev_attr_soc_uid ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct soc_device_attribute* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int imx_scu_get_handle (int /*<<< orphan*/ *) ; 
 int imx_scu_soc_id () ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int of_property_read_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_root ; 
 struct soc_device* soc_device_register (struct soc_device_attribute*) ; 
 int /*<<< orphan*/  soc_device_to_device (struct soc_device*) ; 
 int /*<<< orphan*/  soc_ipc_handle ; 

__attribute__((used)) static int imx_scu_soc_probe(struct platform_device *pdev)
{
	struct soc_device_attribute *soc_dev_attr;
	struct soc_device *soc_dev;
	int id, ret;
	u32 val;

	ret = imx_scu_get_handle(&soc_ipc_handle);
	if (ret)
		return ret;

	soc_dev_attr = devm_kzalloc(&pdev->dev, sizeof(*soc_dev_attr),
				    GFP_KERNEL);
	if (!soc_dev_attr)
		return -ENOMEM;

	soc_dev_attr->family = "Freescale i.MX";

	ret = of_property_read_string(of_root,
				      "model",
				      &soc_dev_attr->machine);
	if (ret)
		return ret;

	id = imx_scu_soc_id();
	if (id < 0)
		return -EINVAL;

	/* format soc_id value passed from SCU firmware */
	val = id & 0x1f;
	soc_dev_attr->soc_id = kasprintf(GFP_KERNEL, "0x%x", val);
	if (!soc_dev_attr->soc_id)
		return -ENOMEM;

	/* format revision value passed from SCU firmware */
	val = (id >> 5) & 0xf;
	val = (((val >> 2) + 1) << 4) | (val & 0x3);
	soc_dev_attr->revision = kasprintf(GFP_KERNEL,
					   "%d.%d",
					   (val >> 4) & 0xf,
					   val & 0xf);
	if (!soc_dev_attr->revision) {
		ret = -ENOMEM;
		goto free_soc_id;
	}

	soc_dev = soc_device_register(soc_dev_attr);
	if (IS_ERR(soc_dev)) {
		ret = PTR_ERR(soc_dev);
		goto free_revision;
	}

	ret = device_create_file(soc_device_to_device(soc_dev),
				 &dev_attr_soc_uid);
	if (ret)
		goto free_revision;

	return 0;

free_revision:
	kfree(soc_dev_attr->revision);
free_soc_id:
	kfree(soc_dev_attr->soc_id);
	return ret;
}