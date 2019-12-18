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
typedef  int u32 ;
struct bcm2835_host {TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int SDHSTS_CRC16_ERROR ; 
 int SDHSTS_FIFO_ERROR ; 
 int SDHSTS_REW_TIME_OUT ; 

__attribute__((used)) static void bcm2835_check_data_error(struct bcm2835_host *host, u32 intmask)
{
	if (!host->data)
		return;
	if (intmask & (SDHSTS_CRC16_ERROR | SDHSTS_FIFO_ERROR))
		host->data->error = -EILSEQ;
	if (intmask & SDHSTS_REW_TIME_OUT)
		host->data->error = -ETIMEDOUT;
}