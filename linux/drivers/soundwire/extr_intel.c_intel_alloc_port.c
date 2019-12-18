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
typedef  void* u32 ;
struct sdw_cdns {int num_ports; int /*<<< orphan*/  pdm; int /*<<< orphan*/  pcm; int /*<<< orphan*/  dev; struct sdw_cdns_port* ports; } ;
struct sdw_intel {struct sdw_cdns cdns; } ;
struct sdw_cdns_port {int assigned; int /*<<< orphan*/  pdi; void* ch; void* direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  intel_pdi_alh_configure (struct sdw_intel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pdi_shim_configure (struct sdw_intel*,int /*<<< orphan*/ ) ; 
 int sdw_cdns_alloc_stream (struct sdw_cdns*,int /*<<< orphan*/ *,struct sdw_cdns_port*,void*,void*) ; 
 int /*<<< orphan*/  sdw_cdns_config_stream (struct sdw_cdns*,struct sdw_cdns_port*,void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sdw_cdns_port *intel_alloc_port(struct sdw_intel *sdw,
					      u32 ch, u32 dir, bool pcm)
{
	struct sdw_cdns *cdns = &sdw->cdns;
	struct sdw_cdns_port *port = NULL;
	int i, ret = 0;

	for (i = 0; i < cdns->num_ports; i++) {
		if (cdns->ports[i].assigned)
			continue;

		port = &cdns->ports[i];
		port->assigned = true;
		port->direction = dir;
		port->ch = ch;
		break;
	}

	if (!port) {
		dev_err(cdns->dev, "Unable to find a free port\n");
		return NULL;
	}

	if (pcm) {
		ret = sdw_cdns_alloc_stream(cdns, &cdns->pcm, port, ch, dir);
		if (ret)
			goto out;

		intel_pdi_shim_configure(sdw, port->pdi);
		sdw_cdns_config_stream(cdns, port, ch, dir, port->pdi);

		intel_pdi_alh_configure(sdw, port->pdi);

	} else {
		ret = sdw_cdns_alloc_stream(cdns, &cdns->pdm, port, ch, dir);
	}

out:
	if (ret) {
		port->assigned = false;
		port = NULL;
	}

	return port;
}