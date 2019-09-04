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
typedef  size_t u8 ;
typedef  int u32 ;
struct pcap_chip {size_t adc_head; int /*<<< orphan*/  adc_mutex; TYPE_1__** adc_queue; } ;
struct TYPE_2__ {int flags; scalar_t__ bank; } ;

/* Variables and functions */
 int PCAP_ADC_ADEN ; 
 int PCAP_ADC_AD_SEL1 ; 
 scalar_t__ PCAP_ADC_BANK_1 ; 
 int PCAP_ADC_TS_M_MASK ; 
 int PCAP_ADC_TS_REF_LOWPWR ; 
 int PCAP_ADR_ASC ; 
 int /*<<< orphan*/  PCAP_REG_ADC ; 
 int /*<<< orphan*/  PCAP_REG_ADR ; 
 int /*<<< orphan*/  ezx_pcap_read (struct pcap_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ezx_pcap_write (struct pcap_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_disable_adc (struct pcap_chip*) ; 

__attribute__((used)) static void pcap_adc_trigger(struct pcap_chip *pcap)
{
	u32 tmp;
	u8 head;

	mutex_lock(&pcap->adc_mutex);
	head = pcap->adc_head;
	if (!pcap->adc_queue[head]) {
		/* queue is empty, save power */
		pcap_disable_adc(pcap);
		mutex_unlock(&pcap->adc_mutex);
		return;
	}
	/* start conversion on requested bank, save TS_M bits */
	ezx_pcap_read(pcap, PCAP_REG_ADC, &tmp);
	tmp &= (PCAP_ADC_TS_M_MASK | PCAP_ADC_TS_REF_LOWPWR);
	tmp |= pcap->adc_queue[head]->flags | PCAP_ADC_ADEN;

	if (pcap->adc_queue[head]->bank == PCAP_ADC_BANK_1)
		tmp |= PCAP_ADC_AD_SEL1;

	ezx_pcap_write(pcap, PCAP_REG_ADC, tmp);
	mutex_unlock(&pcap->adc_mutex);
	ezx_pcap_write(pcap, PCAP_REG_ADR, PCAP_ADR_ASC);
}