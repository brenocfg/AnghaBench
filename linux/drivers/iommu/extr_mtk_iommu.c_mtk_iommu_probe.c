#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {TYPE_2__* of_node; } ;
struct platform_device {struct device dev; } ;
struct mtk_iommu_data {int enable_4GB; scalar_t__ irq; int /*<<< orphan*/  list; int /*<<< orphan*/  iommu; TYPE_1__* larb_imu; int /*<<< orphan*/  bclk; TYPE_3__* plat_data; int /*<<< orphan*/  base; int /*<<< orphan*/  protect_base; struct device* dev; } ;
struct device_node {int dummy; } ;
struct component_match {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_7__ {scalar_t__ has_bclk; int /*<<< orphan*/  has_4gb_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int BIT_ULL (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MTK_PROTECT_PA_ALIGN ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_set_iommu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compare_of ; 
 int component_master_add_with_match (struct device*,int /*<<< orphan*/ *,struct component_match*) ; 
 int /*<<< orphan*/  component_match_add_release (struct device*,struct component_match**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int iommu_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_fwnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iommu_device_sysfs_add (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_present (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m4ulist ; 
 int max_pfn ; 
 int /*<<< orphan*/  mtk_iommu_com_ops ; 
 int mtk_iommu_hw_init (struct mtk_iommu_data*) ; 
 int /*<<< orphan*/  mtk_iommu_ops ; 
 int of_count_phandle_with_args (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 TYPE_3__* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (TYPE_2__*,char*,int) ; 
 int of_property_read_u32 (struct device_node*,char*,size_t*) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_iommu_data*) ; 
 int /*<<< orphan*/  release_of ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static int mtk_iommu_probe(struct platform_device *pdev)
{
	struct mtk_iommu_data   *data;
	struct device           *dev = &pdev->dev;
	struct resource         *res;
	resource_size_t		ioaddr;
	struct component_match  *match = NULL;
	void                    *protect;
	int                     i, larb_nr, ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	data->dev = dev;
	data->plat_data = of_device_get_match_data(dev);

	/* Protect memory. HW will access here while translation fault.*/
	protect = devm_kzalloc(dev, MTK_PROTECT_PA_ALIGN * 2, GFP_KERNEL);
	if (!protect)
		return -ENOMEM;
	data->protect_base = ALIGN(virt_to_phys(protect), MTK_PROTECT_PA_ALIGN);

	/* Whether the current dram is over 4GB */
	data->enable_4GB = !!(max_pfn > (BIT_ULL(32) >> PAGE_SHIFT));
	if (!data->plat_data->has_4gb_mode)
		data->enable_4GB = false;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(data->base))
		return PTR_ERR(data->base);
	ioaddr = res->start;

	data->irq = platform_get_irq(pdev, 0);
	if (data->irq < 0)
		return data->irq;

	if (data->plat_data->has_bclk) {
		data->bclk = devm_clk_get(dev, "bclk");
		if (IS_ERR(data->bclk))
			return PTR_ERR(data->bclk);
	}

	larb_nr = of_count_phandle_with_args(dev->of_node,
					     "mediatek,larbs", NULL);
	if (larb_nr < 0)
		return larb_nr;

	for (i = 0; i < larb_nr; i++) {
		struct device_node *larbnode;
		struct platform_device *plarbdev;
		u32 id;

		larbnode = of_parse_phandle(dev->of_node, "mediatek,larbs", i);
		if (!larbnode)
			return -EINVAL;

		if (!of_device_is_available(larbnode)) {
			of_node_put(larbnode);
			continue;
		}

		ret = of_property_read_u32(larbnode, "mediatek,larb-id", &id);
		if (ret)/* The id is consecutive if there is no this property */
			id = i;

		plarbdev = of_find_device_by_node(larbnode);
		if (!plarbdev) {
			of_node_put(larbnode);
			return -EPROBE_DEFER;
		}
		data->larb_imu[id].dev = &plarbdev->dev;

		component_match_add_release(dev, &match, release_of,
					    compare_of, larbnode);
	}

	platform_set_drvdata(pdev, data);

	ret = mtk_iommu_hw_init(data);
	if (ret)
		return ret;

	ret = iommu_device_sysfs_add(&data->iommu, dev, NULL,
				     "mtk-iommu.%pa", &ioaddr);
	if (ret)
		return ret;

	iommu_device_set_ops(&data->iommu, &mtk_iommu_ops);
	iommu_device_set_fwnode(&data->iommu, &pdev->dev.of_node->fwnode);

	ret = iommu_device_register(&data->iommu);
	if (ret)
		return ret;

	list_add_tail(&data->list, &m4ulist);

	if (!iommu_present(&platform_bus_type))
		bus_set_iommu(&platform_bus_type, &mtk_iommu_ops);

	return component_master_add_with_match(dev, &mtk_iommu_com_ops, match);
}