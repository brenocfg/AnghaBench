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
 int /*<<< orphan*/  SG2_S0_GPIO_DETECT ; 
 int /*<<< orphan*/  SG2_S0_GPIO_READY ; 
 size_t SOC_STAT_CD ; 
 size_t SOC_STAT_RDY ; 

__attribute__((used)) static int sg2_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	skt->stat[SOC_STAT_CD].gpio = SG2_S0_GPIO_DETECT;
	skt->stat[SOC_STAT_CD].name = "PCMCIA0 CD";
	skt->stat[SOC_STAT_RDY].gpio = SG2_S0_GPIO_READY;
	skt->stat[SOC_STAT_RDY].name = "PCMCIA0 RDY";
	return 0;
}