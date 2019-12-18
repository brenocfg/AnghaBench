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
typedef  int u32 ;
struct pcap_keys {int /*<<< orphan*/  input; int /*<<< orphan*/  pcap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_HP ; 
 int /*<<< orphan*/  KEY_POWER ; 
#define  PCAP_IRQ_MIC 129 
#define  PCAP_IRQ_ONOFF 128 
 int /*<<< orphan*/  PCAP_REG_PSTAT ; 
 int /*<<< orphan*/  ezx_pcap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int irq_to_pcap (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t pcap_keys_handler(int irq, void *_pcap_keys)
{
	struct pcap_keys *pcap_keys = _pcap_keys;
	int pirq = irq_to_pcap(pcap_keys->pcap, irq);
	u32 pstat;

	ezx_pcap_read(pcap_keys->pcap, PCAP_REG_PSTAT, &pstat);
	pstat &= 1 << pirq;

	switch (pirq) {
	case PCAP_IRQ_ONOFF:
		input_report_key(pcap_keys->input, KEY_POWER, !pstat);
		break;
	case PCAP_IRQ_MIC:
		input_report_key(pcap_keys->input, KEY_HP, !pstat);
		break;
	}

	input_sync(pcap_keys->input);

	return IRQ_HANDLED;
}