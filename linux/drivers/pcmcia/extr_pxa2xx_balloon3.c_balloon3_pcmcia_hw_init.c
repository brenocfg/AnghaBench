#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  pci_irq; } ;
struct soc_pcmcia_socket {TYPE_2__* stat; TYPE_1__ socket; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  irq; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BALLOON3_BP_CF_NRDY_IRQ ; 
 int /*<<< orphan*/  BALLOON3_BP_NSTSCHG_IRQ ; 
 int /*<<< orphan*/  BALLOON3_FPGA_VER ; 
 int /*<<< orphan*/  BALLOON3_GPIO_S0_CD ; 
 size_t SOC_STAT_BVD1 ; 
 size_t SOC_STAT_CD ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int balloon3_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	uint16_t ver;

	ver = __raw_readw(BALLOON3_FPGA_VER);
	if (ver < 0x4f08)
		pr_warn("The FPGA code, version 0x%04x, is too old. "
			"PCMCIA/CF support might be broken in this version!",
			ver);

	skt->socket.pci_irq = BALLOON3_BP_CF_NRDY_IRQ;
	skt->stat[SOC_STAT_CD].gpio = BALLOON3_GPIO_S0_CD;
	skt->stat[SOC_STAT_CD].name = "PCMCIA0 CD";
	skt->stat[SOC_STAT_BVD1].irq = BALLOON3_BP_NSTSCHG_IRQ;
	skt->stat[SOC_STAT_BVD1].name = "PCMCIA0 STSCHG";

	return 0;
}