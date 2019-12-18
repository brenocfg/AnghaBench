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
struct ibmveth_adapter {int /*<<< orphan*/  rx_no_buffer; int /*<<< orphan*/ * buffer_list_addr; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  be64_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmveth_update_rx_no_buffer(struct ibmveth_adapter *adapter)
{
	__be64 *p = adapter->buffer_list_addr + 4096 - 8;

	adapter->rx_no_buffer = be64_to_cpup(p);
}