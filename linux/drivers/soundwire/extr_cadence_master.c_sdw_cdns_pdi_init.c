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
struct sdw_cdns_streams {int num_bd; int num_in; int num_out; int num_pdi; int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  bd; } ;
struct sdw_cdns_stream_config {int pcm_bd; int pcm_in; int pcm_out; int pdm_bd; int pdm_in; int pdm_out; } ;
struct sdw_cdns {int num_ports; TYPE_1__* ports; int /*<<< orphan*/  dev; struct sdw_cdns_streams pdm; struct sdw_cdns_streams pcm; } ;
struct TYPE_2__ {int assigned; int num; } ;

/* Variables and functions */
 int CDNS_PCM_PDI_OFFSET ; 
 int CDNS_PDM_PDI_OFFSET ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cdns_allocate_pdi (struct sdw_cdns*,int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int sdw_cdns_pdi_init(struct sdw_cdns *cdns,
		      struct sdw_cdns_stream_config config)
{
	struct sdw_cdns_streams *stream;
	int offset, i, ret;

	cdns->pcm.num_bd = config.pcm_bd;
	cdns->pcm.num_in = config.pcm_in;
	cdns->pcm.num_out = config.pcm_out;
	cdns->pdm.num_bd = config.pdm_bd;
	cdns->pdm.num_in = config.pdm_in;
	cdns->pdm.num_out = config.pdm_out;

	/* Allocate PDIs for PCMs */
	stream = &cdns->pcm;

	/* First two PDIs are reserved for bulk transfers */
	if (stream->num_bd < CDNS_PCM_PDI_OFFSET)
		return -EINVAL;
	stream->num_bd -= CDNS_PCM_PDI_OFFSET;
	offset = CDNS_PCM_PDI_OFFSET;

	ret = cdns_allocate_pdi(cdns, &stream->bd,
				stream->num_bd, offset);
	if (ret)
		return ret;

	offset += stream->num_bd;

	ret = cdns_allocate_pdi(cdns, &stream->in,
				stream->num_in, offset);
	if (ret)
		return ret;

	offset += stream->num_in;

	ret = cdns_allocate_pdi(cdns, &stream->out,
				stream->num_out, offset);
	if (ret)
		return ret;

	/* Update total number of PCM PDIs */
	stream->num_pdi = stream->num_bd + stream->num_in + stream->num_out;
	cdns->num_ports = stream->num_pdi;

	/* Allocate PDIs for PDMs */
	stream = &cdns->pdm;
	offset = CDNS_PDM_PDI_OFFSET;
	ret = cdns_allocate_pdi(cdns, &stream->bd,
				stream->num_bd, offset);
	if (ret)
		return ret;

	offset += stream->num_bd;

	ret = cdns_allocate_pdi(cdns, &stream->in,
				stream->num_in, offset);
	if (ret)
		return ret;

	offset += stream->num_in;

	ret = cdns_allocate_pdi(cdns, &stream->out,
				stream->num_out, offset);
	if (ret)
		return ret;

	/* Update total number of PDM PDIs */
	stream->num_pdi = stream->num_bd + stream->num_in + stream->num_out;
	cdns->num_ports += stream->num_pdi;

	cdns->ports = devm_kcalloc(cdns->dev, cdns->num_ports,
				   sizeof(*cdns->ports), GFP_KERNEL);
	if (!cdns->ports) {
		ret = -ENOMEM;
		return ret;
	}

	for (i = 0; i < cdns->num_ports; i++) {
		cdns->ports[i].assigned = false;
		cdns->ports[i].num = i + 1; /* Port 0 reserved for bulk */
	}

	return 0;
}