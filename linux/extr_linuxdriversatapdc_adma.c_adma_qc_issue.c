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
struct TYPE_4__ {int protocol; } ;
struct ata_queued_cmd {TYPE_2__ tf; TYPE_1__* ap; } ;
struct adma_port_priv {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {struct adma_port_priv* private_data; } ;

/* Variables and functions */
#define  ATAPI_PROT_DMA 129 
#define  ATA_PROT_DMA 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  adma_packet_start (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  adma_state_mmio ; 
 int /*<<< orphan*/  adma_state_pkt ; 
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 

__attribute__((used)) static unsigned int adma_qc_issue(struct ata_queued_cmd *qc)
{
	struct adma_port_priv *pp = qc->ap->private_data;

	switch (qc->tf.protocol) {
	case ATA_PROT_DMA:
		pp->state = adma_state_pkt;
		adma_packet_start(qc);
		return 0;

	case ATAPI_PROT_DMA:
		BUG();
		break;

	default:
		break;
	}

	pp->state = adma_state_mmio;
	return ata_sff_qc_issue(qc);
}