#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pci_irq; } ;
struct soc_pcmcia_socket {size_t nr; TYPE_1__ socket; TYPE_2__* stat; } ;
struct TYPE_6__ {scalar_t__ cd_irq; int /*<<< orphan*/  irq; int /*<<< orphan*/  cd_irq_str; } ;
struct TYPE_5__ {scalar_t__ irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_3__* SCOOP_DEV ; 
 size_t SOC_STAT_CD ; 

__attribute__((used)) static int sharpsl_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	if (SCOOP_DEV[skt->nr].cd_irq >= 0) {
		skt->stat[SOC_STAT_CD].irq = SCOOP_DEV[skt->nr].cd_irq;
		skt->stat[SOC_STAT_CD].name = SCOOP_DEV[skt->nr].cd_irq_str;
	}

	skt->socket.pci_irq = SCOOP_DEV[skt->nr].irq;

	return 0;
}