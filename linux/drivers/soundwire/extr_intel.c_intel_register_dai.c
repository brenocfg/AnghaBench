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
struct snd_soc_dai_driver {int dummy; } ;
struct sdw_cdns_streams {int num_pdi; int /*<<< orphan*/  num_ch_bd; scalar_t__ num_bd; scalar_t__ num_out; int /*<<< orphan*/  num_ch_out; scalar_t__ num_in; int /*<<< orphan*/  num_ch_in; } ;
struct sdw_cdns {int /*<<< orphan*/  dev; struct sdw_cdns_streams pdm; struct sdw_cdns_streams pcm; } ;
struct sdw_intel {struct sdw_cdns cdns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTEL_PDI_BD ; 
 int /*<<< orphan*/  INTEL_PDI_IN ; 
 int /*<<< orphan*/  INTEL_PDI_OUT ; 
 int /*<<< orphan*/  dai_component ; 
 struct snd_soc_dai_driver* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int intel_create_dai (struct sdw_cdns*,struct snd_soc_dai_driver*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int snd_soc_register_component (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct snd_soc_dai_driver*,int) ; 

__attribute__((used)) static int intel_register_dai(struct sdw_intel *sdw)
{
	struct sdw_cdns *cdns = &sdw->cdns;
	struct sdw_cdns_streams *stream;
	struct snd_soc_dai_driver *dais;
	int num_dai, ret, off = 0;

	/* DAIs are created based on total number of PDIs supported */
	num_dai = cdns->pcm.num_pdi + cdns->pdm.num_pdi;

	dais = devm_kcalloc(cdns->dev, num_dai, sizeof(*dais), GFP_KERNEL);
	if (!dais)
		return -ENOMEM;

	/* Create PCM DAIs */
	stream = &cdns->pcm;

	ret = intel_create_dai(cdns, dais, INTEL_PDI_IN, cdns->pcm.num_in,
			       off, stream->num_ch_in, true);
	if (ret)
		return ret;

	off += cdns->pcm.num_in;
	ret = intel_create_dai(cdns, dais, INTEL_PDI_OUT, cdns->pcm.num_out,
			       off, stream->num_ch_out, true);
	if (ret)
		return ret;

	off += cdns->pcm.num_out;
	ret = intel_create_dai(cdns, dais, INTEL_PDI_BD, cdns->pcm.num_bd,
			       off, stream->num_ch_bd, true);
	if (ret)
		return ret;

	/* Create PDM DAIs */
	stream = &cdns->pdm;
	off += cdns->pcm.num_bd;
	ret = intel_create_dai(cdns, dais, INTEL_PDI_IN, cdns->pdm.num_in,
			       off, stream->num_ch_in, false);
	if (ret)
		return ret;

	off += cdns->pdm.num_in;
	ret = intel_create_dai(cdns, dais, INTEL_PDI_OUT, cdns->pdm.num_out,
			       off, stream->num_ch_out, false);
	if (ret)
		return ret;

	off += cdns->pdm.num_out;
	ret = intel_create_dai(cdns, dais, INTEL_PDI_BD, cdns->pdm.num_bd,
			       off, stream->num_ch_bd, false);
	if (ret)
		return ret;

	return snd_soc_register_component(cdns->dev, &dai_component,
					  dais, num_dai);
}