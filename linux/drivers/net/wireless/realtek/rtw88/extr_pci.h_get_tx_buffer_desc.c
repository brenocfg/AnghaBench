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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int wp; int /*<<< orphan*/ * head; } ;
struct rtw_pci_tx_ring {TYPE_1__ r; } ;
struct rtw_pci_tx_buffer_desc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct rtw_pci_tx_buffer_desc *get_tx_buffer_desc(struct rtw_pci_tx_ring *ring,
						  u32 size)
{
	u8 *buf_desc;

	buf_desc = ring->r.head + ring->r.wp * size;
	return (struct rtw_pci_tx_buffer_desc *)buf_desc;
}