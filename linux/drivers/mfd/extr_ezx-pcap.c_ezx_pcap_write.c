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
typedef  int u8 ;
typedef  int u32 ;
struct pcap_chip {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int PCAP_REGISTER_ADDRESS_SHIFT ; 
 int PCAP_REGISTER_VALUE_MASK ; 
 int PCAP_REGISTER_WRITE_OP_BIT ; 
 int ezx_pcap_putget (struct pcap_chip*,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ezx_pcap_write(struct pcap_chip *pcap, u8 reg_num, u32 value)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&pcap->io_lock, flags);
	value &= PCAP_REGISTER_VALUE_MASK;
	value |= PCAP_REGISTER_WRITE_OP_BIT
		| (reg_num << PCAP_REGISTER_ADDRESS_SHIFT);
	ret = ezx_pcap_putget(pcap, &value);
	spin_unlock_irqrestore(&pcap->io_lock, flags);

	return ret;
}