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
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcf50633_adc_sync_read_callback(struct pcf50633 *pcf, void *param,
	int result)
{
	struct pcf50633_adc_sync_request *req = param;

	req->result = result;
	complete(&req->completion);
}