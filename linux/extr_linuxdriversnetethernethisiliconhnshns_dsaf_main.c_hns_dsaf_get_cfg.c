#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct regmap {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct dsaf_device {int dsaf_mode; TYPE_2__* dev; int /*<<< orphan*/  misc_op; int /*<<< orphan*/  buf_size_type; void* buf_size; void* reset_offset; void* desc_num; void* io_base; int /*<<< orphan*/  ppe_paddr; void* ppe_base; struct regmap* sub_ctrl; void* sds_base; void* sc_base; int /*<<< orphan*/  dsaf_tc_mode; int /*<<< orphan*/  dsaf_en; TYPE_1__ ae_dev; void* dsaf_ver; } ;
struct device_node {int dummy; } ;
typedef  enum dsaf_mode { ____Placeholder_dsaf_mode } dsaf_mode ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {int /*<<< orphan*/  fwnode; struct device_node* of_node; } ;

/* Variables and functions */
 void* AE_VERSION_1 ; 
 void* AE_VERSION_2 ; 
 int /*<<< orphan*/  DMA_BIT_MASK (unsigned long long) ; 
 int DSAF_MODE_DISABLE_2PORT_8VM ; 
 int DSAF_MODE_DISABLE_6PORT_2VM ; 
 int DSAF_MODE_ENABLE ; 
 int DSAF_MODE_ENABLE_16VM ; 
 int DSAF_MODE_INVALID ; 
 int DSAF_MODE_MAX ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  HNS_DSAF_IS_DEBUG (struct dsaf_device*) ; 
 void* HNS_DSAF_MAX_DESC_CNT ; 
 void* HNS_DSAF_MIN_DESC_CNT ; 
 int /*<<< orphan*/  HRD_DSAF_4TC_MODE ; 
 int /*<<< orphan*/  HRD_DSAF_8TC_MODE ; 
 int /*<<< orphan*/  HRD_DSAF_MODE ; 
 int /*<<< orphan*/  HRD_DSAF_NO_DSAF_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct regmap*) ; 
 int PTR_ERR (void*) ; 
 scalar_t__ acpi_dev_found (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 scalar_t__ dev_of_node (TYPE_2__*) ; 
 int device_property_read_string (TYPE_2__*,char*,char const**) ; 
 int device_property_read_u32 (TYPE_2__*,char*,void**) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  dma_set_mask_and_coherent (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__* g_dsaf_mode_match ; 
 TYPE_3__* hns_dsaf_acpi_match ; 
 int /*<<< orphan*/  hns_misc_op_get (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_rcb_buf_size2type (void*) ; 
 scalar_t__ is_acpi_node (int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,void*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 
 struct platform_device* to_platform_device (TYPE_2__*) ; 

__attribute__((used)) static int hns_dsaf_get_cfg(struct dsaf_device *dsaf_dev)
{
	int ret, i;
	u32 desc_num;
	u32 buf_size;
	u32 reset_offset = 0;
	u32 res_idx = 0;
	const char *mode_str;
	struct regmap *syscon;
	struct resource *res;
	struct device_node *np = dsaf_dev->dev->of_node, *np_temp;
	struct platform_device *pdev = to_platform_device(dsaf_dev->dev);

	if (dev_of_node(dsaf_dev->dev)) {
		if (of_device_is_compatible(np, "hisilicon,hns-dsaf-v1"))
			dsaf_dev->dsaf_ver = AE_VERSION_1;
		else
			dsaf_dev->dsaf_ver = AE_VERSION_2;
	} else if (is_acpi_node(dsaf_dev->dev->fwnode)) {
		if (acpi_dev_found(hns_dsaf_acpi_match[0].id))
			dsaf_dev->dsaf_ver = AE_VERSION_1;
		else if (acpi_dev_found(hns_dsaf_acpi_match[1].id))
			dsaf_dev->dsaf_ver = AE_VERSION_2;
		else
			return -ENXIO;
	} else {
		dev_err(dsaf_dev->dev, "cannot get cfg data from of or acpi\n");
		return -ENXIO;
	}

	ret = device_property_read_string(dsaf_dev->dev, "mode", &mode_str);
	if (ret) {
		dev_err(dsaf_dev->dev, "get dsaf mode fail, ret=%d!\n", ret);
		return ret;
	}
	for (i = 0; i < DSAF_MODE_MAX; i++) {
		if (g_dsaf_mode_match[i] &&
		    !strcmp(mode_str, g_dsaf_mode_match[i]))
			break;
	}
	if (i >= DSAF_MODE_MAX ||
	    i == DSAF_MODE_INVALID || i == DSAF_MODE_ENABLE) {
		dev_err(dsaf_dev->dev,
			"%s prs mode str fail!\n", dsaf_dev->ae_dev.name);
		return -EINVAL;
	}
	dsaf_dev->dsaf_mode = (enum dsaf_mode)i;

	if (dsaf_dev->dsaf_mode > DSAF_MODE_ENABLE)
		dsaf_dev->dsaf_en = HRD_DSAF_NO_DSAF_MODE;
	else
		dsaf_dev->dsaf_en = HRD_DSAF_MODE;

	if ((i == DSAF_MODE_ENABLE_16VM) ||
	    (i == DSAF_MODE_DISABLE_2PORT_8VM) ||
	    (i == DSAF_MODE_DISABLE_6PORT_2VM))
		dsaf_dev->dsaf_tc_mode = HRD_DSAF_8TC_MODE;
	else
		dsaf_dev->dsaf_tc_mode = HRD_DSAF_4TC_MODE;

	if (dev_of_node(dsaf_dev->dev)) {
		np_temp = of_parse_phandle(np, "subctrl-syscon", 0);
		syscon = syscon_node_to_regmap(np_temp);
		of_node_put(np_temp);
		if (IS_ERR_OR_NULL(syscon)) {
			res = platform_get_resource(pdev, IORESOURCE_MEM,
						    res_idx++);
			if (!res) {
				dev_err(dsaf_dev->dev, "subctrl info is needed!\n");
				return -ENOMEM;
			}

			dsaf_dev->sc_base = devm_ioremap_resource(&pdev->dev,
								  res);
			if (IS_ERR(dsaf_dev->sc_base))
				return PTR_ERR(dsaf_dev->sc_base);

			res = platform_get_resource(pdev, IORESOURCE_MEM,
						    res_idx++);
			if (!res) {
				dev_err(dsaf_dev->dev, "serdes-ctrl info is needed!\n");
				return -ENOMEM;
			}

			dsaf_dev->sds_base = devm_ioremap_resource(&pdev->dev,
								   res);
			if (IS_ERR(dsaf_dev->sds_base))
				return PTR_ERR(dsaf_dev->sds_base);
		} else {
			dsaf_dev->sub_ctrl = syscon;
		}
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "ppe-base");
	if (!res) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, res_idx++);
		if (!res) {
			dev_err(dsaf_dev->dev, "ppe-base info is needed!\n");
			return -ENOMEM;
		}
	}
	dsaf_dev->ppe_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(dsaf_dev->ppe_base))
		return PTR_ERR(dsaf_dev->ppe_base);
	dsaf_dev->ppe_paddr = res->start;

	if (!HNS_DSAF_IS_DEBUG(dsaf_dev)) {
		res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
						   "dsaf-base");
		if (!res) {
			res = platform_get_resource(pdev, IORESOURCE_MEM,
						    res_idx);
			if (!res) {
				dev_err(dsaf_dev->dev,
					"dsaf-base info is needed!\n");
				return -ENOMEM;
			}
		}
		dsaf_dev->io_base = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(dsaf_dev->io_base))
			return PTR_ERR(dsaf_dev->io_base);
	}

	ret = device_property_read_u32(dsaf_dev->dev, "desc-num", &desc_num);
	if (ret < 0 || desc_num < HNS_DSAF_MIN_DESC_CNT ||
	    desc_num > HNS_DSAF_MAX_DESC_CNT) {
		dev_err(dsaf_dev->dev, "get desc-num(%d) fail, ret=%d!\n",
			desc_num, ret);
		return -EINVAL;
	}
	dsaf_dev->desc_num = desc_num;

	ret = device_property_read_u32(dsaf_dev->dev, "reset-field-offset",
				       &reset_offset);
	if (ret < 0) {
		dev_dbg(dsaf_dev->dev,
			"get reset-field-offset fail, ret=%d!\r\n", ret);
	}
	dsaf_dev->reset_offset = reset_offset;

	ret = device_property_read_u32(dsaf_dev->dev, "buf-size", &buf_size);
	if (ret < 0) {
		dev_err(dsaf_dev->dev,
			"get buf-size fail, ret=%d!\r\n", ret);
		return ret;
	}
	dsaf_dev->buf_size = buf_size;

	dsaf_dev->buf_size_type = hns_rcb_buf_size2type(buf_size);
	if (dsaf_dev->buf_size_type < 0) {
		dev_err(dsaf_dev->dev,
			"buf_size(%d) is wrong!\n", buf_size);
		return -EINVAL;
	}

	dsaf_dev->misc_op = hns_misc_op_get(dsaf_dev);
	if (!dsaf_dev->misc_op)
		return -ENOMEM;

	if (!dma_set_mask_and_coherent(dsaf_dev->dev, DMA_BIT_MASK(64ULL)))
		dev_dbg(dsaf_dev->dev, "set mask to 64bit\n");
	else
		dev_err(dsaf_dev->dev, "set mask to 64bit fail!\n");

	return 0;
}