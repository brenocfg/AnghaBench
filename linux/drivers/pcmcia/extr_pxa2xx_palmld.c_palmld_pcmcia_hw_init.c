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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_NR_PALMLD_PCMCIA_READY ; 
 size_t SOC_STAT_RDY ; 
 int gpio_request_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  palmld_pcmcia_gpios ; 

__attribute__((used)) static int palmld_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	int ret;

	ret = gpio_request_array(palmld_pcmcia_gpios,
				ARRAY_SIZE(palmld_pcmcia_gpios));

	skt->stat[SOC_STAT_RDY].gpio = GPIO_NR_PALMLD_PCMCIA_READY;
	skt->stat[SOC_STAT_RDY].name = "PCMCIA Ready";

	return ret;
}