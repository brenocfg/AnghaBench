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
struct vb2_queue {int dummy; } ;
struct sg_table {int /*<<< orphan*/  sgl; } ;
struct cx88_riscmem {int /*<<< orphan*/  dma; scalar_t__ cpu; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  vb2_buf; } ;
struct cx88_buffer {TYPE_1__ vb; struct cx88_riscmem risc; } ;
struct cx8802_dev {int ts_packet_size; int ts_packet_count; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int EINVAL ; 
 int cx88_risc_databuffer (int /*<<< orphan*/ ,struct cx88_riscmem*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cx88_riscmem*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct sg_table* vb2_dma_sg_plane_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vb2_plane_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int cx8802_buf_prepare(struct vb2_queue *q, struct cx8802_dev *dev,
		       struct cx88_buffer *buf)
{
	int size = dev->ts_packet_size * dev->ts_packet_count;
	struct sg_table *sgt = vb2_dma_sg_plane_desc(&buf->vb.vb2_buf, 0);
	struct cx88_riscmem *risc = &buf->risc;
	int rc;

	if (vb2_plane_size(&buf->vb.vb2_buf, 0) < size)
		return -EINVAL;
	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, size);

	rc = cx88_risc_databuffer(dev->pci, risc, sgt->sgl,
				  dev->ts_packet_size, dev->ts_packet_count, 0);
	if (rc) {
		if (risc->cpu)
			pci_free_consistent(dev->pci, risc->size,
					    risc->cpu, risc->dma);
		memset(risc, 0, sizeof(*risc));
		return rc;
	}
	return 0;
}