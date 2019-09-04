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
struct bcm2835_host {scalar_t__ blocks; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_finish_data (struct bcm2835_host*) ; 

__attribute__((used)) static void bcm2835_data_threaded_irq(struct bcm2835_host *host)
{
	if (!host->data)
		return;
	if ((host->blocks == 0) || host->data->error)
		bcm2835_finish_data(host);
}