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
struct pcf50633_adc_sync_request {int result; int /*<<< orphan*/  completion; } ;
struct pcf50633 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int pcf50633_adc_async_read (struct pcf50633*,int,int,int /*<<< orphan*/ ,struct pcf50633_adc_sync_request*) ; 
 int /*<<< orphan*/  pcf50633_adc_sync_read_callback ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int pcf50633_adc_sync_read(struct pcf50633 *pcf, int mux, int avg)
{
	struct pcf50633_adc_sync_request req;
	int ret;

	init_completion(&req.completion);

	ret = pcf50633_adc_async_read(pcf, mux, avg,
		pcf50633_adc_sync_read_callback, &req);
	if (ret)
		return ret;

	wait_for_completion(&req.completion);

	return req.result;
}