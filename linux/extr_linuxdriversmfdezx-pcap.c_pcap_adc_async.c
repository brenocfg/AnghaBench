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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pcap_chip {size_t adc_tail; int /*<<< orphan*/  adc_mutex; struct pcap_adc_request** adc_queue; } ;
struct pcap_adc_request {void* data; void* callback; void** ch; int /*<<< orphan*/  flags; void* bank; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PCAP_ADC_MAXQ ; 
 int /*<<< orphan*/  kfree (struct pcap_adc_request*) ; 
 struct pcap_adc_request* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_adc_trigger (struct pcap_chip*) ; 

int pcap_adc_async(struct pcap_chip *pcap, u8 bank, u32 flags, u8 ch[],
						void *callback, void *data)
{
	struct pcap_adc_request *req;

	/* This will be freed after we have a result */
	req = kmalloc(sizeof(struct pcap_adc_request), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	req->bank = bank;
	req->flags = flags;
	req->ch[0] = ch[0];
	req->ch[1] = ch[1];
	req->callback = callback;
	req->data = data;

	mutex_lock(&pcap->adc_mutex);
	if (pcap->adc_queue[pcap->adc_tail]) {
		mutex_unlock(&pcap->adc_mutex);
		kfree(req);
		return -EBUSY;
	}
	pcap->adc_queue[pcap->adc_tail] = req;
	pcap->adc_tail = (pcap->adc_tail + 1) & (PCAP_ADC_MAXQ - 1);
	mutex_unlock(&pcap->adc_mutex);

	/* start conversion */
	pcap_adc_trigger(pcap);

	return 0;
}