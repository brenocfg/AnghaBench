#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* name; } ;
struct TYPE_14__ {void* name; int /*<<< orphan*/  dai_name; } ;
struct TYPE_13__ {void* dai_name; } ;
struct TYPE_11__ {int maxburst; int /*<<< orphan*/  addr_width; int /*<<< orphan*/  addr; } ;
struct snd_soc_card {int num_links; char* name; struct device* dev; struct snd_soc_dai_link* dai_link; } ;
struct snd_soc_dai_link {int num_cpus; int num_codecs; int num_platforms; char* name; char* stream_name; TYPE_6__* platforms; TYPE_5__* codecs; TYPE_4__* cpus; } ;
struct TYPE_12__ {TYPE_6__ platform; TYPE_5__ codec; TYPE_4__ cpu; TYPE_2__ dma_data; struct snd_soc_card card; struct snd_soc_dai_link link; } ;
struct vc4_hdmi {TYPE_3__ audio; TYPE_1__* pdev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int VC4_HD_MAI_DATA ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int devm_snd_dmaengine_pcm_register (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,struct snd_soc_card*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 int /*<<< orphan*/  of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_get_address (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcm_conf ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct vc4_hdmi*) ; 
 TYPE_7__ vc4_hdmi_audio_codec_dai_drv ; 
 int /*<<< orphan*/  vc4_hdmi_audio_component_drv ; 
 int /*<<< orphan*/  vc4_hdmi_audio_cpu_dai_comp ; 
 TYPE_7__ vc4_hdmi_audio_cpu_dai_drv ; 

__attribute__((used)) static int vc4_hdmi_audio_init(struct vc4_hdmi *hdmi)
{
	struct snd_soc_dai_link *dai_link = &hdmi->audio.link;
	struct snd_soc_card *card = &hdmi->audio.card;
	struct device *dev = &hdmi->pdev->dev;
	const __be32 *addr;
	int ret;

	if (!of_find_property(dev->of_node, "dmas", NULL)) {
		dev_warn(dev,
			 "'dmas' DT property is missing, no HDMI audio\n");
		return 0;
	}

	/*
	 * Get the physical address of VC4_HD_MAI_DATA. We need to retrieve
	 * the bus address specified in the DT, because the physical address
	 * (the one returned by platform_get_resource()) is not appropriate
	 * for DMA transfers.
	 * This VC/MMU should probably be exposed to avoid this kind of hacks.
	 */
	addr = of_get_address(dev->of_node, 1, NULL, NULL);
	hdmi->audio.dma_data.addr = be32_to_cpup(addr) + VC4_HD_MAI_DATA;
	hdmi->audio.dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	hdmi->audio.dma_data.maxburst = 2;

	ret = devm_snd_dmaengine_pcm_register(dev, &pcm_conf, 0);
	if (ret) {
		dev_err(dev, "Could not register PCM component: %d\n", ret);
		return ret;
	}

	ret = devm_snd_soc_register_component(dev, &vc4_hdmi_audio_cpu_dai_comp,
					      &vc4_hdmi_audio_cpu_dai_drv, 1);
	if (ret) {
		dev_err(dev, "Could not register CPU DAI: %d\n", ret);
		return ret;
	}

	/* register component and codec dai */
	ret = devm_snd_soc_register_component(dev, &vc4_hdmi_audio_component_drv,
				     &vc4_hdmi_audio_codec_dai_drv, 1);
	if (ret) {
		dev_err(dev, "Could not register component: %d\n", ret);
		return ret;
	}

	dai_link->cpus		= &hdmi->audio.cpu;
	dai_link->codecs	= &hdmi->audio.codec;
	dai_link->platforms	= &hdmi->audio.platform;

	dai_link->num_cpus	= 1;
	dai_link->num_codecs	= 1;
	dai_link->num_platforms	= 1;

	dai_link->name = "MAI";
	dai_link->stream_name = "MAI PCM";
	dai_link->codecs->dai_name = vc4_hdmi_audio_codec_dai_drv.name;
	dai_link->cpus->dai_name = dev_name(dev);
	dai_link->codecs->name = dev_name(dev);
	dai_link->platforms->name = dev_name(dev);

	card->dai_link = dai_link;
	card->num_links = 1;
	card->name = "vc4-hdmi";
	card->dev = dev;

	/*
	 * Be careful, snd_soc_register_card() calls dev_set_drvdata() and
	 * stores a pointer to the snd card object in dev->driver_data. This
	 * means we cannot use it for something else. The hdmi back-pointer is
	 * now stored in card->drvdata and should be retrieved with
	 * snd_soc_card_get_drvdata() if needed.
	 */
	snd_soc_card_set_drvdata(card, hdmi);
	ret = devm_snd_soc_register_card(dev, card);
	if (ret)
		dev_err(dev, "Could not register sound card: %d\n", ret);

	return ret;

}