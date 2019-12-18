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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pcap_chip {int dummy; } ;
struct pcap_adc_sync_request {int /*<<< orphan*/ * res; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int pcap_adc_async (struct pcap_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pcap_adc_sync_request*) ; 
 int /*<<< orphan*/  pcap_adc_sync_cb ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int pcap_adc_sync(struct pcap_chip *pcap, u8 bank, u32 flags, u8 ch[],
								u16 res[])
{
	struct pcap_adc_sync_request sync_data;
	int ret;

	init_completion(&sync_data.completion);
	ret = pcap_adc_async(pcap, bank, flags, ch, pcap_adc_sync_cb,
								&sync_data);
	if (ret)
		return ret;
	wait_for_completion(&sync_data.completion);
	res[0] = sync_data.res[0];
	res[1] = sync_data.res[1];

	return 0;
}