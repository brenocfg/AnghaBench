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
struct softing_platform_data {int generation; } ;
struct resource {int flags; } ;
struct pcmcia_device {struct resource** resource; } ;

/* Variables and functions */
 int ERANGE ; 
 size_t PCMCIA_IOMEM_0 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WIN_DATA_WIDTH_16 ; 
 int WIN_DATA_WIDTH_8 ; 
 int WIN_ENABLE ; 
 int WIN_MEMORY_TYPE_CM ; 
 int WIN_USE_WAIT ; 
 int pcmcia_request_window (struct pcmcia_device*,struct resource*,int) ; 
 int resource_size (struct resource*) ; 

__attribute__((used)) static int softingcs_probe_config(struct pcmcia_device *pcmcia, void *priv_data)
{
	struct softing_platform_data *pdat = priv_data;
	struct resource *pres;
	int memspeed = 0;

	WARN_ON(!pdat);
	pres = pcmcia->resource[PCMCIA_IOMEM_0];
	if (resource_size(pres) < 0x1000)
		return -ERANGE;

	pres->flags |= WIN_MEMORY_TYPE_CM | WIN_ENABLE;
	if (pdat->generation < 2) {
		pres->flags |= WIN_USE_WAIT | WIN_DATA_WIDTH_8;
		memspeed = 3;
	} else {
		pres->flags |= WIN_DATA_WIDTH_16;
	}
	return pcmcia_request_window(pcmcia, pres, memspeed);
}