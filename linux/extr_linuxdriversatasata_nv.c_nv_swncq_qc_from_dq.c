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
struct defer_queue {int head; int tail; unsigned int* tag; int defer_bits; } ;
struct nv_swncq_port_priv {struct defer_queue defer_queue; } ;
struct ata_queued_cmd {int dummy; } ;
struct ata_port {struct nv_swncq_port_priv* private_data; } ;

/* Variables and functions */
 int ATA_MAX_QUEUE ; 
 unsigned int ATA_TAG_POISON ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ata_queued_cmd* ata_qc_from_tag (struct ata_port*,unsigned int) ; 

__attribute__((used)) static struct ata_queued_cmd *nv_swncq_qc_from_dq(struct ata_port *ap)
{
	struct nv_swncq_port_priv *pp = ap->private_data;
	struct defer_queue *dq = &pp->defer_queue;
	unsigned int tag;

	if (dq->head == dq->tail)	/* null queue */
		return NULL;

	tag = dq->tag[dq->head & (ATA_MAX_QUEUE - 1)];
	dq->tag[dq->head++ & (ATA_MAX_QUEUE - 1)] = ATA_TAG_POISON;
	WARN_ON(!(dq->defer_bits & (1 << tag)));
	dq->defer_bits &= ~(1 << tag);

	return ata_qc_from_tag(ap, tag);
}