#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct regmap_config {int dummy; } ;
struct platform_device_info {char* name; int size_data; void* dma_mask; struct dw_hdmi_i2s_audio_data* data; int /*<<< orphan*/  id; struct device* parent; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct dw_hdmi_plat_data {int /*<<< orphan*/ * regm; } ;
struct dw_hdmi_i2s_audio_data {int irq; int (* read ) (struct dw_hdmi*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * ops; struct dw_hdmi* hdmi; int /*<<< orphan*/  write; int /*<<< orphan*/  eld; int /*<<< orphan*/ * base; int /*<<< orphan*/  phys; } ;
struct dw_hdmi_cec_data {int irq; int (* read ) (struct dw_hdmi*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * ops; struct dw_hdmi* hdmi; int /*<<< orphan*/  write; int /*<<< orphan*/  eld; int /*<<< orphan*/ * base; int /*<<< orphan*/  phys; } ;
struct dw_hdmi_audio_data {int irq; int (* read ) (struct dw_hdmi*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * ops; struct dw_hdmi* hdmi; int /*<<< orphan*/  write; int /*<<< orphan*/  eld; int /*<<< orphan*/ * base; int /*<<< orphan*/  phys; } ;
struct TYPE_7__ {int /*<<< orphan*/  eld; } ;
struct TYPE_6__ {struct device_node* of_node; int /*<<< orphan*/ * funcs; struct dw_hdmi* driver_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct dw_hdmi {int sample_rate; int disabled; int rxsense; int phy_mask; int mc_clkdis; int reg_shift; int version; int /*<<< orphan*/ * ddc; int /*<<< orphan*/ * isfr_clk; int /*<<< orphan*/ * cec_clk; int /*<<< orphan*/ * iahb_clk; TYPE_4__* i2c; void* cec; void* audio; int /*<<< orphan*/  disable_audio; int /*<<< orphan*/  enable_audio; TYPE_3__ connector; int /*<<< orphan*/ * regs; TYPE_2__ bridge; int /*<<< orphan*/ * unwedge_state; int /*<<< orphan*/ * default_state; int /*<<< orphan*/ * pinctrl; TYPE_1__ phy; struct device* dev; int /*<<< orphan*/ * regm; int /*<<< orphan*/  audio_lock; int /*<<< orphan*/  cec_notifier_mutex; int /*<<< orphan*/  audio_mutex; int /*<<< orphan*/  mutex; struct dw_hdmi_plat_data const* plat_data; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  pdevinfo ;
typedef  int /*<<< orphan*/  cec ;
typedef  int /*<<< orphan*/  audio ;
struct TYPE_8__ {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 void* DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 struct dw_hdmi* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HDMI_CONFIG0_CEC ; 
 int HDMI_CONFIG0_I2S ; 
 int /*<<< orphan*/  HDMI_CONFIG0_ID ; 
 int HDMI_CONFIG3_AHBAUDDMA ; 
 int /*<<< orphan*/  HDMI_CONFIG3_ID ; 
 int /*<<< orphan*/  HDMI_DESIGN_ID ; 
 int HDMI_PHY_HPD ; 
 int HDMI_PHY_RX_SENSE ; 
 int /*<<< orphan*/  HDMI_PRODUCT_ID0 ; 
 int HDMI_PRODUCT_ID0_HDMI_TX ; 
 int /*<<< orphan*/  HDMI_PRODUCT_ID1 ; 
 int HDMI_PRODUCT_ID1_HDCP ; 
 int HDMI_PRODUCT_ID1_HDMI_TX ; 
 int /*<<< orphan*/  HDMI_REVISION_ID ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct dw_hdmi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_pinctrl_get (struct device*) ; 
 int /*<<< orphan*/ * devm_regmap_init_mmio (struct device*,int /*<<< orphan*/ *,struct regmap_config const*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dw_hdmi*) ; 
 int /*<<< orphan*/  dw_hdmi_ahb_audio_disable ; 
 int /*<<< orphan*/  dw_hdmi_ahb_audio_enable ; 
 int /*<<< orphan*/  dw_hdmi_bridge_funcs ; 
 int /*<<< orphan*/  dw_hdmi_cec_ops ; 
 int dw_hdmi_detect_phy (struct dw_hdmi*) ; 
 int /*<<< orphan*/  dw_hdmi_hardirq ; 
 int /*<<< orphan*/ * dw_hdmi_i2c_adapter (struct dw_hdmi*) ; 
 int /*<<< orphan*/  dw_hdmi_i2s_audio_disable ; 
 int /*<<< orphan*/  dw_hdmi_i2s_audio_enable ; 
 int /*<<< orphan*/  dw_hdmi_init_hw (struct dw_hdmi*) ; 
 int /*<<< orphan*/  dw_hdmi_irq ; 
 int /*<<< orphan*/  hdmi_init_clk_regenerator (struct dw_hdmi*) ; 
 int hdmi_readb (struct dw_hdmi*,int /*<<< orphan*/ ) ; 
 struct regmap_config hdmi_regmap_32bit_config ; 
 struct regmap_config hdmi_regmap_8bit_config ; 
 int /*<<< orphan*/  hdmi_writeb ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct platform_device_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_get_i2c_adapter_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 void* pinctrl_lookup_state (int /*<<< orphan*/ *,char*) ; 
 void* platform_device_register_full (struct platform_device_info*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dw_hdmi *
__dw_hdmi_probe(struct platform_device *pdev,
		const struct dw_hdmi_plat_data *plat_data)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct platform_device_info pdevinfo;
	struct device_node *ddc_node;
	struct dw_hdmi_cec_data cec;
	struct dw_hdmi *hdmi;
	struct resource *iores = NULL;
	int irq;
	int ret;
	u32 val = 1;
	u8 prod_id0;
	u8 prod_id1;
	u8 config0;
	u8 config3;

	hdmi = devm_kzalloc(dev, sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi)
		return ERR_PTR(-ENOMEM);

	hdmi->plat_data = plat_data;
	hdmi->dev = dev;
	hdmi->sample_rate = 48000;
	hdmi->disabled = true;
	hdmi->rxsense = true;
	hdmi->phy_mask = (u8)~(HDMI_PHY_HPD | HDMI_PHY_RX_SENSE);
	hdmi->mc_clkdis = 0x7f;

	mutex_init(&hdmi->mutex);
	mutex_init(&hdmi->audio_mutex);
	mutex_init(&hdmi->cec_notifier_mutex);
	spin_lock_init(&hdmi->audio_lock);

	ddc_node = of_parse_phandle(np, "ddc-i2c-bus", 0);
	if (ddc_node) {
		hdmi->ddc = of_get_i2c_adapter_by_node(ddc_node);
		of_node_put(ddc_node);
		if (!hdmi->ddc) {
			dev_dbg(hdmi->dev, "failed to read ddc node\n");
			return ERR_PTR(-EPROBE_DEFER);
		}

	} else {
		dev_dbg(hdmi->dev, "no ddc property found\n");
	}

	if (!plat_data->regm) {
		const struct regmap_config *reg_config;

		of_property_read_u32(np, "reg-io-width", &val);
		switch (val) {
		case 4:
			reg_config = &hdmi_regmap_32bit_config;
			hdmi->reg_shift = 2;
			break;
		case 1:
			reg_config = &hdmi_regmap_8bit_config;
			break;
		default:
			dev_err(dev, "reg-io-width must be 1 or 4\n");
			return ERR_PTR(-EINVAL);
		}

		iores = platform_get_resource(pdev, IORESOURCE_MEM, 0);
		hdmi->regs = devm_ioremap_resource(dev, iores);
		if (IS_ERR(hdmi->regs)) {
			ret = PTR_ERR(hdmi->regs);
			goto err_res;
		}

		hdmi->regm = devm_regmap_init_mmio(dev, hdmi->regs, reg_config);
		if (IS_ERR(hdmi->regm)) {
			dev_err(dev, "Failed to configure regmap\n");
			ret = PTR_ERR(hdmi->regm);
			goto err_res;
		}
	} else {
		hdmi->regm = plat_data->regm;
	}

	hdmi->isfr_clk = devm_clk_get(hdmi->dev, "isfr");
	if (IS_ERR(hdmi->isfr_clk)) {
		ret = PTR_ERR(hdmi->isfr_clk);
		dev_err(hdmi->dev, "Unable to get HDMI isfr clk: %d\n", ret);
		goto err_res;
	}

	ret = clk_prepare_enable(hdmi->isfr_clk);
	if (ret) {
		dev_err(hdmi->dev, "Cannot enable HDMI isfr clock: %d\n", ret);
		goto err_res;
	}

	hdmi->iahb_clk = devm_clk_get(hdmi->dev, "iahb");
	if (IS_ERR(hdmi->iahb_clk)) {
		ret = PTR_ERR(hdmi->iahb_clk);
		dev_err(hdmi->dev, "Unable to get HDMI iahb clk: %d\n", ret);
		goto err_isfr;
	}

	ret = clk_prepare_enable(hdmi->iahb_clk);
	if (ret) {
		dev_err(hdmi->dev, "Cannot enable HDMI iahb clock: %d\n", ret);
		goto err_isfr;
	}

	hdmi->cec_clk = devm_clk_get(hdmi->dev, "cec");
	if (PTR_ERR(hdmi->cec_clk) == -ENOENT) {
		hdmi->cec_clk = NULL;
	} else if (IS_ERR(hdmi->cec_clk)) {
		ret = PTR_ERR(hdmi->cec_clk);
		if (ret != -EPROBE_DEFER)
			dev_err(hdmi->dev, "Cannot get HDMI cec clock: %d\n",
				ret);

		hdmi->cec_clk = NULL;
		goto err_iahb;
	} else {
		ret = clk_prepare_enable(hdmi->cec_clk);
		if (ret) {
			dev_err(hdmi->dev, "Cannot enable HDMI cec clock: %d\n",
				ret);
			goto err_iahb;
		}
	}

	/* Product and revision IDs */
	hdmi->version = (hdmi_readb(hdmi, HDMI_DESIGN_ID) << 8)
		      | (hdmi_readb(hdmi, HDMI_REVISION_ID) << 0);
	prod_id0 = hdmi_readb(hdmi, HDMI_PRODUCT_ID0);
	prod_id1 = hdmi_readb(hdmi, HDMI_PRODUCT_ID1);

	if (prod_id0 != HDMI_PRODUCT_ID0_HDMI_TX ||
	    (prod_id1 & ~HDMI_PRODUCT_ID1_HDCP) != HDMI_PRODUCT_ID1_HDMI_TX) {
		dev_err(dev, "Unsupported HDMI controller (%04x:%02x:%02x)\n",
			hdmi->version, prod_id0, prod_id1);
		ret = -ENODEV;
		goto err_iahb;
	}

	ret = dw_hdmi_detect_phy(hdmi);
	if (ret < 0)
		goto err_iahb;

	dev_info(dev, "Detected HDMI TX controller v%x.%03x %s HDCP (%s)\n",
		 hdmi->version >> 12, hdmi->version & 0xfff,
		 prod_id1 & HDMI_PRODUCT_ID1_HDCP ? "with" : "without",
		 hdmi->phy.name);

	dw_hdmi_init_hw(hdmi);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto err_iahb;
	}

	ret = devm_request_threaded_irq(dev, irq, dw_hdmi_hardirq,
					dw_hdmi_irq, IRQF_SHARED,
					dev_name(dev), hdmi);
	if (ret)
		goto err_iahb;

	/*
	 * To prevent overflows in HDMI_IH_FC_STAT2, set the clk regenerator
	 * N and cts values before enabling phy
	 */
	hdmi_init_clk_regenerator(hdmi);

	/* If DDC bus is not specified, try to register HDMI I2C bus */
	if (!hdmi->ddc) {
		/* Look for (optional) stuff related to unwedging */
		hdmi->pinctrl = devm_pinctrl_get(dev);
		if (!IS_ERR(hdmi->pinctrl)) {
			hdmi->unwedge_state =
				pinctrl_lookup_state(hdmi->pinctrl, "unwedge");
			hdmi->default_state =
				pinctrl_lookup_state(hdmi->pinctrl, "default");

			if (IS_ERR(hdmi->default_state) ||
			    IS_ERR(hdmi->unwedge_state)) {
				if (!IS_ERR(hdmi->unwedge_state))
					dev_warn(dev,
						 "Unwedge requires default pinctrl\n");
				hdmi->default_state = NULL;
				hdmi->unwedge_state = NULL;
			}
		}

		hdmi->ddc = dw_hdmi_i2c_adapter(hdmi);
		if (IS_ERR(hdmi->ddc))
			hdmi->ddc = NULL;
	}

	hdmi->bridge.driver_private = hdmi;
	hdmi->bridge.funcs = &dw_hdmi_bridge_funcs;
#ifdef CONFIG_OF
	hdmi->bridge.of_node = pdev->dev.of_node;
#endif

	memset(&pdevinfo, 0, sizeof(pdevinfo));
	pdevinfo.parent = dev;
	pdevinfo.id = PLATFORM_DEVID_AUTO;

	config0 = hdmi_readb(hdmi, HDMI_CONFIG0_ID);
	config3 = hdmi_readb(hdmi, HDMI_CONFIG3_ID);

	if (iores && config3 & HDMI_CONFIG3_AHBAUDDMA) {
		struct dw_hdmi_audio_data audio;

		audio.phys = iores->start;
		audio.base = hdmi->regs;
		audio.irq = irq;
		audio.hdmi = hdmi;
		audio.eld = hdmi->connector.eld;
		hdmi->enable_audio = dw_hdmi_ahb_audio_enable;
		hdmi->disable_audio = dw_hdmi_ahb_audio_disable;

		pdevinfo.name = "dw-hdmi-ahb-audio";
		pdevinfo.data = &audio;
		pdevinfo.size_data = sizeof(audio);
		pdevinfo.dma_mask = DMA_BIT_MASK(32);
		hdmi->audio = platform_device_register_full(&pdevinfo);
	} else if (config0 & HDMI_CONFIG0_I2S) {
		struct dw_hdmi_i2s_audio_data audio;

		audio.hdmi	= hdmi;
		audio.eld	= hdmi->connector.eld;
		audio.write	= hdmi_writeb;
		audio.read	= hdmi_readb;
		hdmi->enable_audio = dw_hdmi_i2s_audio_enable;
		hdmi->disable_audio = dw_hdmi_i2s_audio_disable;

		pdevinfo.name = "dw-hdmi-i2s-audio";
		pdevinfo.data = &audio;
		pdevinfo.size_data = sizeof(audio);
		pdevinfo.dma_mask = DMA_BIT_MASK(32);
		hdmi->audio = platform_device_register_full(&pdevinfo);
	}

	if (config0 & HDMI_CONFIG0_CEC) {
		cec.hdmi = hdmi;
		cec.ops = &dw_hdmi_cec_ops;
		cec.irq = irq;

		pdevinfo.name = "dw-hdmi-cec";
		pdevinfo.data = &cec;
		pdevinfo.size_data = sizeof(cec);
		pdevinfo.dma_mask = 0;

		hdmi->cec = platform_device_register_full(&pdevinfo);
	}

	return hdmi;

err_iahb:
	if (hdmi->i2c) {
		i2c_del_adapter(&hdmi->i2c->adap);
		hdmi->ddc = NULL;
	}

	clk_disable_unprepare(hdmi->iahb_clk);
	if (hdmi->cec_clk)
		clk_disable_unprepare(hdmi->cec_clk);
err_isfr:
	clk_disable_unprepare(hdmi->isfr_clk);
err_res:
	i2c_put_adapter(hdmi->ddc);

	return ERR_PTR(ret);
}