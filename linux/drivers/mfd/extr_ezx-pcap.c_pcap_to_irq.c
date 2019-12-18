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
struct pcap_chip {int irq_base; } ;

/* Variables and functions */

int pcap_to_irq(struct pcap_chip *pcap, int irq)
{
	return pcap->irq_base + irq;
}