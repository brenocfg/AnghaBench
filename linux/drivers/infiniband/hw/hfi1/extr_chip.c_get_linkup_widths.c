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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_link_widths (struct hfi1_devdata*,int*,int*) ; 
 int link_width_to_bits (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  read_vc_local_link_mode (struct hfi1_devdata*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void get_linkup_widths(struct hfi1_devdata *dd, u16 *tx_width,
			      u16 *rx_width)
{
	u16 widths, tx, rx;
	u8 misc_bits, local_flags;
	u16 active_tx, active_rx;

	read_vc_local_link_mode(dd, &misc_bits, &local_flags, &widths);
	tx = widths >> 12;
	rx = (widths >> 8) & 0xf;

	*tx_width = link_width_to_bits(dd, tx);
	*rx_width = link_width_to_bits(dd, rx);

	/* print the active widths */
	get_link_widths(dd, &active_tx, &active_rx);
}