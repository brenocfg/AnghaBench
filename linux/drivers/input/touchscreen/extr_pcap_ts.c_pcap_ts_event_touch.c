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
struct pcap_ts {scalar_t__ read_state; int /*<<< orphan*/  work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PCAP_ADC_TS_M_PRESSURE ; 
 scalar_t__ PCAP_ADC_TS_M_STANDBY ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pcap_ts_event_touch(int pirq, void *data)
{
	struct pcap_ts *pcap_ts = data;

	if (pcap_ts->read_state == PCAP_ADC_TS_M_STANDBY) {
		pcap_ts->read_state = PCAP_ADC_TS_M_PRESSURE;
		schedule_delayed_work(&pcap_ts->work, 0);
	}
	return IRQ_HANDLED;
}