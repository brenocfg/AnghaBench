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
struct qcom_pcie_resources_2_3_3 {void** rst; void* aux_clk; void* ahb_clk; void* axi_s_clk; void* axi_m_clk; void* iface; } ;
struct TYPE_2__ {struct qcom_pcie_resources_2_3_3 v2_3_3; } ;
struct qcom_pcie {struct dw_pcie* pci; TYPE_1__ res; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_reset_control_get (struct device*,char const*) ; 

__attribute__((used)) static int qcom_pcie_get_resources_2_3_3(struct qcom_pcie *pcie)
{
	struct qcom_pcie_resources_2_3_3 *res = &pcie->res.v2_3_3;
	struct dw_pcie *pci = pcie->pci;
	struct device *dev = pci->dev;
	int i;
	const char *rst_names[] = { "axi_m", "axi_s", "pipe",
				    "axi_m_sticky", "sticky",
				    "ahb", "sleep", };

	res->iface = devm_clk_get(dev, "iface");
	if (IS_ERR(res->iface))
		return PTR_ERR(res->iface);

	res->axi_m_clk = devm_clk_get(dev, "axi_m");
	if (IS_ERR(res->axi_m_clk))
		return PTR_ERR(res->axi_m_clk);

	res->axi_s_clk = devm_clk_get(dev, "axi_s");
	if (IS_ERR(res->axi_s_clk))
		return PTR_ERR(res->axi_s_clk);

	res->ahb_clk = devm_clk_get(dev, "ahb");
	if (IS_ERR(res->ahb_clk))
		return PTR_ERR(res->ahb_clk);

	res->aux_clk = devm_clk_get(dev, "aux");
	if (IS_ERR(res->aux_clk))
		return PTR_ERR(res->aux_clk);

	for (i = 0; i < ARRAY_SIZE(rst_names); i++) {
		res->rst[i] = devm_reset_control_get(dev, rst_names[i]);
		if (IS_ERR(res->rst[i]))
			return PTR_ERR(res->rst[i]);
	}

	return 0;
}