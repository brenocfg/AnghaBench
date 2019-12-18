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
struct niu_parent {int num_ports; int* rxchan_per_port; int* txchan_per_port; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void niu_n2_divide_channels(struct niu_parent *parent)
{
	int num_ports = parent->num_ports;
	int i;

	for (i = 0; i < num_ports; i++) {
		parent->rxchan_per_port[i] = (16 / num_ports);
		parent->txchan_per_port[i] = (16 / num_ports);

		pr_info("niu%d: Port %u [%u RX chans] [%u TX chans]\n",
			parent->index, i,
			parent->rxchan_per_port[i],
			parent->txchan_per_port[i]);
	}
}