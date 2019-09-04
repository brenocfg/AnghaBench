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
struct hinic_rxq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rx_alloc_pkts (struct hinic_rxq*) ; 

__attribute__((used)) static void rx_alloc_task(unsigned long data)
{
	struct hinic_rxq *rxq = (struct hinic_rxq *)data;

	(void)rx_alloc_pkts(rxq);
}