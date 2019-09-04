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
typedef  int u16 ;
struct TYPE_3__ {int pkt_size; } ;
struct TYPE_4__ {TYPE_1__ xsum_sz; } ;
struct rx_return_desc {int num_buf; TYPE_2__ xsz; } ;
struct atl1_adapter {int rx_buffer_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl1_clean_alloc_flag (struct atl1_adapter*,struct rx_return_desc*,int) ; 

__attribute__((used)) static void atl1_update_rfd_index(struct atl1_adapter *adapter,
	struct rx_return_desc *rrd)
{
	u16 num_buf;

	num_buf = (rrd->xsz.xsum_sz.pkt_size + adapter->rx_buffer_len - 1) /
		adapter->rx_buffer_len;
	if (rrd->num_buf == num_buf)
		/* clean alloc flag for bad rrd */
		atl1_clean_alloc_flag(adapter, rrd, num_buf);
}