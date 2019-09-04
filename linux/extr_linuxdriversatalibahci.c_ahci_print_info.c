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
typedef  int u32 ;
struct ata_host {int /*<<< orphan*/  dev; struct ahci_host_priv* private_data; } ;
struct ahci_host_priv {int version; int cap; int cap2; int port_map; } ;

/* Variables and functions */
 int HOST_CAP2_APST ; 
 int HOST_CAP2_BOH ; 
 int HOST_CAP2_DESO ; 
 int HOST_CAP2_NVMHCI ; 
 int HOST_CAP2_SADM ; 
 int HOST_CAP2_SDS ; 
 int HOST_CAP_64 ; 
 int HOST_CAP_ALPM ; 
 int HOST_CAP_CCC ; 
 int HOST_CAP_CLO ; 
 int HOST_CAP_EMS ; 
 int HOST_CAP_FBS ; 
 int HOST_CAP_LED ; 
 int HOST_CAP_MPS ; 
 int HOST_CAP_NCQ ; 
 int HOST_CAP_ONLY ; 
 int HOST_CAP_PART ; 
 int HOST_CAP_PIO_MULTI ; 
 int HOST_CAP_PMP ; 
 int HOST_CAP_SNTF ; 
 int HOST_CAP_SSC ; 
 int HOST_CAP_SSS ; 
 int HOST_CAP_SXS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 

void ahci_print_info(struct ata_host *host, const char *scc_s)
{
	struct ahci_host_priv *hpriv = host->private_data;
	u32 vers, cap, cap2, impl, speed;
	const char *speed_s;

	vers = hpriv->version;
	cap = hpriv->cap;
	cap2 = hpriv->cap2;
	impl = hpriv->port_map;

	speed = (cap >> 20) & 0xf;
	if (speed == 1)
		speed_s = "1.5";
	else if (speed == 2)
		speed_s = "3";
	else if (speed == 3)
		speed_s = "6";
	else
		speed_s = "?";

	dev_info(host->dev,
		"AHCI %02x%02x.%02x%02x "
		"%u slots %u ports %s Gbps 0x%x impl %s mode\n"
		,

		(vers >> 24) & 0xff,
		(vers >> 16) & 0xff,
		(vers >> 8) & 0xff,
		vers & 0xff,

		((cap >> 8) & 0x1f) + 1,
		(cap & 0x1f) + 1,
		speed_s,
		impl,
		scc_s);

	dev_info(host->dev,
		"flags: "
		"%s%s%s%s%s%s%s"
		"%s%s%s%s%s%s%s"
		"%s%s%s%s%s%s%s"
		"%s%s\n"
		,

		cap & HOST_CAP_64 ? "64bit " : "",
		cap & HOST_CAP_NCQ ? "ncq " : "",
		cap & HOST_CAP_SNTF ? "sntf " : "",
		cap & HOST_CAP_MPS ? "ilck " : "",
		cap & HOST_CAP_SSS ? "stag " : "",
		cap & HOST_CAP_ALPM ? "pm " : "",
		cap & HOST_CAP_LED ? "led " : "",
		cap & HOST_CAP_CLO ? "clo " : "",
		cap & HOST_CAP_ONLY ? "only " : "",
		cap & HOST_CAP_PMP ? "pmp " : "",
		cap & HOST_CAP_FBS ? "fbs " : "",
		cap & HOST_CAP_PIO_MULTI ? "pio " : "",
		cap & HOST_CAP_SSC ? "slum " : "",
		cap & HOST_CAP_PART ? "part " : "",
		cap & HOST_CAP_CCC ? "ccc " : "",
		cap & HOST_CAP_EMS ? "ems " : "",
		cap & HOST_CAP_SXS ? "sxs " : "",
		cap2 & HOST_CAP2_DESO ? "deso " : "",
		cap2 & HOST_CAP2_SADM ? "sadm " : "",
		cap2 & HOST_CAP2_SDS ? "sds " : "",
		cap2 & HOST_CAP2_APST ? "apst " : "",
		cap2 & HOST_CAP2_NVMHCI ? "nvmp " : "",
		cap2 & HOST_CAP2_BOH ? "boh " : ""
		);
}