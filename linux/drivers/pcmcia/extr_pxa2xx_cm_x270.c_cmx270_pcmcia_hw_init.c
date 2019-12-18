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
struct soc_pcmcia_socket {TYPE_1__* stat; } ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PCMCIA_RESET ; 
 int /*<<< orphan*/  GPIO_PCMCIA_S0_CD_VALID ; 
 int /*<<< orphan*/  GPIO_PCMCIA_S0_RDYINT ; 
 size_t SOC_STAT_CD ; 
 size_t SOC_STAT_RDY ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cmx270_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	int ret = gpio_request(GPIO_PCMCIA_RESET, "PCCard reset");
	if (ret)
		return ret;
	gpio_direction_output(GPIO_PCMCIA_RESET, 0);

	skt->stat[SOC_STAT_CD].gpio = GPIO_PCMCIA_S0_CD_VALID;
	skt->stat[SOC_STAT_CD].name = "PCMCIA0 CD";
	skt->stat[SOC_STAT_RDY].gpio = GPIO_PCMCIA_S0_RDYINT;
	skt->stat[SOC_STAT_RDY].name = "PCMCIA0 RDY";

	return ret;
}