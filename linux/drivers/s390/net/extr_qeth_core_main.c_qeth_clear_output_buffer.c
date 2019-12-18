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
struct qeth_qdio_out_q {int max_elements; int /*<<< orphan*/  set_pci_flags_count; } ;
struct qeth_qdio_out_buffer {int /*<<< orphan*/  state; scalar_t__ bytes; scalar_t__ next_element_to_fill; TYPE_2__* buffer; scalar_t__* is_header; } ;
struct TYPE_4__ {TYPE_1__* element; } ;
struct TYPE_3__ {int sflags; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_QDIO_BUF_EMPTY ; 
 int SBAL_SFLAGS0_PCI_REQ ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qeth_core_header_cache ; 
 int /*<<< orphan*/  qeth_scrub_qdio_buffer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  qeth_tx_complete_buf (struct qeth_qdio_out_buffer*,int,int) ; 

__attribute__((used)) static void qeth_clear_output_buffer(struct qeth_qdio_out_q *queue,
				     struct qeth_qdio_out_buffer *buf,
				     bool error, int budget)
{
	int i;

	/* is PCI flag set on buffer? */
	if (buf->buffer->element[0].sflags & SBAL_SFLAGS0_PCI_REQ)
		atomic_dec(&queue->set_pci_flags_count);

	qeth_tx_complete_buf(buf, error, budget);

	for (i = 0; i < queue->max_elements; ++i) {
		if (buf->buffer->element[i].addr && buf->is_header[i])
			kmem_cache_free(qeth_core_header_cache,
				buf->buffer->element[i].addr);
		buf->is_header[i] = 0;
	}

	qeth_scrub_qdio_buffer(buf->buffer, queue->max_elements);
	buf->next_element_to_fill = 0;
	buf->bytes = 0;
	atomic_set(&buf->state, QETH_QDIO_BUF_EMPTY);
}