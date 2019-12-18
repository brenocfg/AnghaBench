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
typedef  void* u16 ;
struct pcap_adc_sync_request {int /*<<< orphan*/  completion; void** res; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcap_adc_sync_cb(void *param, u16 res[])
{
	struct pcap_adc_sync_request *req = param;

	req->res[0] = res[0];
	req->res[1] = res[1];
	complete(&req->completion);
}