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
typedef  int u32 ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct fimc_variant {int min_inp_pixsize; int min_out_pixsize; int min_vsize_align; int hor_offs_align; int has_inp_rot; int has_out_rot; void* has_cam_if; void* has_isp_wb; void* has_mainscaler_ext; struct fimc_pix_limit* pix_limit; } ;
struct fimc_pix_limit {int scaler_en_w; int scaler_dis_w; int out_rot_en_w; int out_rot_dis_w; } ;
struct fimc_dev {struct fimc_variant* variant; int /*<<< orphan*/  id; int /*<<< orphan*/  drv_data; TYPE_1__* pdev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FIMC_DEF_HEIGHT_ALIGN ; 
 int FIMC_DEF_HOR_OFFS_ALIGN ; 
 int FIMC_DEF_MIN_SIZE ; 
 int FIMC_PIX_LIMITS_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct fimc_variant* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_of_match ; 
 int /*<<< orphan*/  of_alias_get_id (struct device_node*,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int of_property_read_u32_array (struct device_node*,char*,int*,int) ; 

__attribute__((used)) static int fimc_parse_dt(struct fimc_dev *fimc, u32 *clk_freq)
{
	struct device *dev = &fimc->pdev->dev;
	struct device_node *node = dev->of_node;
	const struct of_device_id *of_id;
	struct fimc_variant *v;
	struct fimc_pix_limit *lim;
	u32 args[FIMC_PIX_LIMITS_MAX];
	int ret;

	if (of_property_read_bool(node, "samsung,lcd-wb"))
		return -ENODEV;

	v = devm_kzalloc(dev, sizeof(*v) + sizeof(*lim), GFP_KERNEL);
	if (!v)
		return -ENOMEM;

	of_id = of_match_node(fimc_of_match, node);
	if (!of_id)
		return -EINVAL;
	fimc->drv_data = of_id->data;
	ret = of_property_read_u32_array(node, "samsung,pix-limits",
					 args, FIMC_PIX_LIMITS_MAX);
	if (ret < 0)
		return ret;

	lim = (struct fimc_pix_limit *)&v[1];

	lim->scaler_en_w = args[0];
	lim->scaler_dis_w = args[1];
	lim->out_rot_en_w = args[2];
	lim->out_rot_dis_w = args[3];
	v->pix_limit = lim;

	ret = of_property_read_u32_array(node, "samsung,min-pix-sizes",
								args, 2);
	v->min_inp_pixsize = ret ? FIMC_DEF_MIN_SIZE : args[0];
	v->min_out_pixsize = ret ? FIMC_DEF_MIN_SIZE : args[1];
	ret = of_property_read_u32_array(node, "samsung,min-pix-alignment",
								args, 2);
	v->min_vsize_align = ret ? FIMC_DEF_HEIGHT_ALIGN : args[0];
	v->hor_offs_align = ret ? FIMC_DEF_HOR_OFFS_ALIGN : args[1];

	ret = of_property_read_u32(node, "samsung,rotators", &args[1]);
	v->has_inp_rot = ret ? 1 : args[1] & 0x01;
	v->has_out_rot = ret ? 1 : args[1] & 0x10;
	v->has_mainscaler_ext = of_property_read_bool(node,
					"samsung,mainscaler-ext");

	v->has_isp_wb = of_property_read_bool(node, "samsung,isp-wb");
	v->has_cam_if = of_property_read_bool(node, "samsung,cam-if");
	of_property_read_u32(node, "clock-frequency", clk_freq);
	fimc->id = of_alias_get_id(node, "fimc");

	fimc->variant = v;
	return 0;
}