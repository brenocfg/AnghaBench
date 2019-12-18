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
struct soc_pcmcia_socket {scalar_t__ nr; TYPE_1__* stat; } ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO12_VPAC270_CF_RDY ; 
 int /*<<< orphan*/  GPIO17_VPAC270_CF_CD ; 
 int /*<<< orphan*/  GPIO35_VPAC270_PCMCIA_RDY ; 
 int /*<<< orphan*/  GPIO84_VPAC270_PCMCIA_CD ; 
 size_t SOC_STAT_CD ; 
 size_t SOC_STAT_RDY ; 
 int gpio_request_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpac270_cf_gpios ; 
 int /*<<< orphan*/  vpac270_pcmcia_gpios ; 

__attribute__((used)) static int vpac270_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	int ret;

	if (skt->nr == 0) {
		ret = gpio_request_array(vpac270_pcmcia_gpios,
				ARRAY_SIZE(vpac270_pcmcia_gpios));

		skt->stat[SOC_STAT_CD].gpio = GPIO84_VPAC270_PCMCIA_CD;
		skt->stat[SOC_STAT_CD].name = "PCMCIA CD";
		skt->stat[SOC_STAT_RDY].gpio = GPIO35_VPAC270_PCMCIA_RDY;
		skt->stat[SOC_STAT_RDY].name = "PCMCIA Ready";
	} else {
		ret = gpio_request_array(vpac270_cf_gpios,
				ARRAY_SIZE(vpac270_cf_gpios));

		skt->stat[SOC_STAT_CD].gpio = GPIO17_VPAC270_CF_CD;
		skt->stat[SOC_STAT_CD].name = "CF CD";
		skt->stat[SOC_STAT_RDY].gpio = GPIO12_VPAC270_CF_RDY;
		skt->stat[SOC_STAT_RDY].name = "CF Ready";
	}

	return ret;
}