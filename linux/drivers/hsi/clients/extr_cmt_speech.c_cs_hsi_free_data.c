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
struct cs_hsi_iface {int /*<<< orphan*/  data_tx_msg; int /*<<< orphan*/  data_rx_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_hsi_free_data_msg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_hsi_free_data(struct cs_hsi_iface *hi)
{
	cs_hsi_free_data_msg(hi->data_rx_msg);
	cs_hsi_free_data_msg(hi->data_tx_msg);
}