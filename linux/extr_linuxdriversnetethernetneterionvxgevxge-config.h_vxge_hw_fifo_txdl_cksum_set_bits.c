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
typedef  int /*<<< orphan*/  u64 ;
struct vxge_hw_fifo_txd {int /*<<< orphan*/  control_1; } ;

/* Variables and functions */

__attribute__((used)) static inline void vxge_hw_fifo_txdl_cksum_set_bits(void *txdlh, u64 cksum_bits)
{
	struct vxge_hw_fifo_txd *txdp = (struct vxge_hw_fifo_txd *)txdlh;
	txdp->control_1 |= cksum_bits;
}