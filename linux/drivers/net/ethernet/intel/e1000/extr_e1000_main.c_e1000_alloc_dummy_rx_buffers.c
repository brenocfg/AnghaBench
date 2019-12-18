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
struct e1000_rx_ring {int dummy; } ;
struct e1000_adapter {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void e1000_alloc_dummy_rx_buffers(struct e1000_adapter *adapter,
					 struct e1000_rx_ring *rx_ring,
					 int cleaned_count)
{
}