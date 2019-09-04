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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct ipu_soc {struct ipu_devtype* devtype; } ;
struct ipu_devtype {scalar_t__ cm_ofs; scalar_t__ srm_ofs; scalar_t__ dc_tmpl_ofs; scalar_t__ disp1_ofs; scalar_t__ disp0_ofs; scalar_t__ vdi_ofs; scalar_t__ tpm_ofs; scalar_t__ ic_ofs; scalar_t__ csi1_ofs; scalar_t__ csi0_ofs; scalar_t__ cpmem_ofs; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPU_CM_DC_REG_OFS ; 
 scalar_t__ IPU_CM_DMFC_REG_OFS ; 
 scalar_t__ IPU_CM_SMFC_REG_OFS ; 
 int /*<<< orphan*/  IPU_CONF_CSI0_EN ; 
 int /*<<< orphan*/  IPU_CONF_CSI1_EN ; 
 int /*<<< orphan*/  IPU_CONF_DI0_EN ; 
 int /*<<< orphan*/  IPU_CONF_DI1_EN ; 
 int IPU_CONF_IC_INPUT ; 
 int IPU_CONF_ISP_EN ; 
 int IPU_CONF_VDI_EN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int) ; 
 int /*<<< orphan*/  ipu_cpmem_exit (struct ipu_soc*) ; 
 int ipu_cpmem_init (struct ipu_soc*,struct device*,scalar_t__) ; 
 int /*<<< orphan*/  ipu_csi_exit (struct ipu_soc*,int) ; 
 int ipu_csi_init (struct ipu_soc*,struct device*,int,scalar_t__,int /*<<< orphan*/ ,struct clk*) ; 
 int /*<<< orphan*/  ipu_dc_exit (struct ipu_soc*) ; 
 int ipu_dc_init (struct ipu_soc*,struct device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ipu_di_exit (struct ipu_soc*,int) ; 
 int ipu_di_init (struct ipu_soc*,struct device*,int,scalar_t__,int /*<<< orphan*/ ,struct clk*) ; 
 int /*<<< orphan*/  ipu_dmfc_exit (struct ipu_soc*) ; 
 int ipu_dmfc_init (struct ipu_soc*,struct device*,scalar_t__,struct clk*) ; 
 int /*<<< orphan*/  ipu_dp_exit (struct ipu_soc*) ; 
 int ipu_dp_init (struct ipu_soc*,struct device*,scalar_t__) ; 
 int /*<<< orphan*/  ipu_ic_exit (struct ipu_soc*) ; 
 int ipu_ic_init (struct ipu_soc*,struct device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ipu_image_convert_exit (struct ipu_soc*) ; 
 int ipu_image_convert_init (struct ipu_soc*,struct device*) ; 
 int ipu_smfc_init (struct ipu_soc*,struct device*,scalar_t__) ; 
 int /*<<< orphan*/  ipu_vdi_exit (struct ipu_soc*) ; 
 int ipu_vdi_init (struct ipu_soc*,struct device*,scalar_t__,int) ; 

__attribute__((used)) static int ipu_submodules_init(struct ipu_soc *ipu,
		struct platform_device *pdev, unsigned long ipu_base,
		struct clk *ipu_clk)
{
	char *unit;
	int ret;
	struct device *dev = &pdev->dev;
	const struct ipu_devtype *devtype = ipu->devtype;

	ret = ipu_cpmem_init(ipu, dev, ipu_base + devtype->cpmem_ofs);
	if (ret) {
		unit = "cpmem";
		goto err_cpmem;
	}

	ret = ipu_csi_init(ipu, dev, 0, ipu_base + devtype->csi0_ofs,
			   IPU_CONF_CSI0_EN, ipu_clk);
	if (ret) {
		unit = "csi0";
		goto err_csi_0;
	}

	ret = ipu_csi_init(ipu, dev, 1, ipu_base + devtype->csi1_ofs,
			   IPU_CONF_CSI1_EN, ipu_clk);
	if (ret) {
		unit = "csi1";
		goto err_csi_1;
	}

	ret = ipu_ic_init(ipu, dev,
			  ipu_base + devtype->ic_ofs,
			  ipu_base + devtype->tpm_ofs);
	if (ret) {
		unit = "ic";
		goto err_ic;
	}

	ret = ipu_vdi_init(ipu, dev, ipu_base + devtype->vdi_ofs,
			   IPU_CONF_VDI_EN | IPU_CONF_ISP_EN |
			   IPU_CONF_IC_INPUT);
	if (ret) {
		unit = "vdi";
		goto err_vdi;
	}

	ret = ipu_image_convert_init(ipu, dev);
	if (ret) {
		unit = "image_convert";
		goto err_image_convert;
	}

	ret = ipu_di_init(ipu, dev, 0, ipu_base + devtype->disp0_ofs,
			  IPU_CONF_DI0_EN, ipu_clk);
	if (ret) {
		unit = "di0";
		goto err_di_0;
	}

	ret = ipu_di_init(ipu, dev, 1, ipu_base + devtype->disp1_ofs,
			IPU_CONF_DI1_EN, ipu_clk);
	if (ret) {
		unit = "di1";
		goto err_di_1;
	}

	ret = ipu_dc_init(ipu, dev, ipu_base + devtype->cm_ofs +
			IPU_CM_DC_REG_OFS, ipu_base + devtype->dc_tmpl_ofs);
	if (ret) {
		unit = "dc_template";
		goto err_dc;
	}

	ret = ipu_dmfc_init(ipu, dev, ipu_base +
			devtype->cm_ofs + IPU_CM_DMFC_REG_OFS, ipu_clk);
	if (ret) {
		unit = "dmfc";
		goto err_dmfc;
	}

	ret = ipu_dp_init(ipu, dev, ipu_base + devtype->srm_ofs);
	if (ret) {
		unit = "dp";
		goto err_dp;
	}

	ret = ipu_smfc_init(ipu, dev, ipu_base +
			devtype->cm_ofs + IPU_CM_SMFC_REG_OFS);
	if (ret) {
		unit = "smfc";
		goto err_smfc;
	}

	return 0;

err_smfc:
	ipu_dp_exit(ipu);
err_dp:
	ipu_dmfc_exit(ipu);
err_dmfc:
	ipu_dc_exit(ipu);
err_dc:
	ipu_di_exit(ipu, 1);
err_di_1:
	ipu_di_exit(ipu, 0);
err_di_0:
	ipu_image_convert_exit(ipu);
err_image_convert:
	ipu_vdi_exit(ipu);
err_vdi:
	ipu_ic_exit(ipu);
err_ic:
	ipu_csi_exit(ipu, 1);
err_csi_1:
	ipu_csi_exit(ipu, 0);
err_csi_0:
	ipu_cpmem_exit(ipu);
err_cpmem:
	dev_err(&pdev->dev, "init %s failed with %d\n", unit, ret);
	return ret;
}