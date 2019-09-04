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
typedef  int /*<<< orphan*/  u32 ;
struct mvneta_rx_queue {void** buf_virt_addr; struct mvneta_rx_desc* descs; } ;
struct mvneta_rx_desc {int /*<<< orphan*/  buf_phys_addr; } ;

/* Variables and functions */

__attribute__((used)) static void mvneta_rx_desc_fill(struct mvneta_rx_desc *rx_desc,
				u32 phys_addr, void *virt_addr,
				struct mvneta_rx_queue *rxq)
{
	int i;

	rx_desc->buf_phys_addr = phys_addr;
	i = rx_desc - rxq->descs;
	rxq->buf_virt_addr[i] = virt_addr;
}