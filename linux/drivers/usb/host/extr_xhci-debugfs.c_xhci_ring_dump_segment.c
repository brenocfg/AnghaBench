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
struct TYPE_2__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_1__ generic; } ;
struct xhci_segment {scalar_t__ dma; union xhci_trb* trbs; } ;
struct seq_file {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int TRBS_PER_SEGMENT ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_decode_trb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xhci_ring_dump_segment(struct seq_file *s,
				   struct xhci_segment *seg)
{
	int			i;
	dma_addr_t		dma;
	union xhci_trb		*trb;

	for (i = 0; i < TRBS_PER_SEGMENT; i++) {
		trb = &seg->trbs[i];
		dma = seg->dma + i * sizeof(*trb);
		seq_printf(s, "%pad: %s\n", &dma,
			   xhci_decode_trb(le32_to_cpu(trb->generic.field[0]),
					   le32_to_cpu(trb->generic.field[1]),
					   le32_to_cpu(trb->generic.field[2]),
					   le32_to_cpu(trb->generic.field[3])));
	}
}