#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int avail; TYPE_5__* cur; } ;
struct ksz_hw {scalar_t__ tx_size; TYPE_4__ tx_desc_info; scalar_t__ tx_int_mask; scalar_t__ tx_int_cnt; } ;
struct TYPE_6__ {int first_seg; } ;
struct TYPE_7__ {TYPE_1__ tx; } ;
struct TYPE_8__ {TYPE_2__ buf; } ;
struct TYPE_10__ {TYPE_3__ sw; } ;

/* Variables and functions */
 scalar_t__ MAX_TX_HELD_SIZE ; 
 int /*<<< orphan*/  get_tx_pkt (TYPE_4__*,TYPE_5__**) ; 

__attribute__((used)) static int hw_alloc_pkt(struct ksz_hw *hw, int length, int physical)
{
	/* Always leave one descriptor free. */
	if (hw->tx_desc_info.avail <= 1)
		return 0;

	/* Allocate a descriptor for transmission and mark it current. */
	get_tx_pkt(&hw->tx_desc_info, &hw->tx_desc_info.cur);
	hw->tx_desc_info.cur->sw.buf.tx.first_seg = 1;

	/* Keep track of number of transmit descriptors used so far. */
	++hw->tx_int_cnt;
	hw->tx_size += length;

	/* Cannot hold on too much data. */
	if (hw->tx_size >= MAX_TX_HELD_SIZE)
		hw->tx_int_cnt = hw->tx_int_mask + 1;

	if (physical > hw->tx_desc_info.avail)
		return 1;

	return hw->tx_desc_info.avail;
}