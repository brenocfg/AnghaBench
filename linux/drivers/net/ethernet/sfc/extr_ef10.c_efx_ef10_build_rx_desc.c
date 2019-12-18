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
struct efx_rx_queue {int dummy; } ;
struct efx_rx_buffer {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_QWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESF_DZ_RX_KER_BUF_ADDR ; 
 int /*<<< orphan*/  ESF_DZ_RX_KER_BYTE_CNT ; 
 struct efx_rx_buffer* efx_rx_buffer (struct efx_rx_queue*,unsigned int) ; 
 int /*<<< orphan*/ * efx_rx_desc (struct efx_rx_queue*,unsigned int) ; 

__attribute__((used)) static inline void
efx_ef10_build_rx_desc(struct efx_rx_queue *rx_queue, unsigned int index)
{
	struct efx_rx_buffer *rx_buf;
	efx_qword_t *rxd;

	rxd = efx_rx_desc(rx_queue, index);
	rx_buf = efx_rx_buffer(rx_queue, index);
	EFX_POPULATE_QWORD_2(*rxd,
			     ESF_DZ_RX_KER_BYTE_CNT, rx_buf->len,
			     ESF_DZ_RX_KER_BUF_ADDR, rx_buf->dma_addr);
}