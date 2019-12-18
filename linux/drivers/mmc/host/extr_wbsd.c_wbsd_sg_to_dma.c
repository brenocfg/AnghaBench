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
struct wbsd_host {int /*<<< orphan*/  dma_buffer; } ;
struct mmc_data {int sg_len; TYPE_1__* sg; } ;
struct TYPE_2__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_copy_to_buffer (TYPE_1__*,int,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void wbsd_sg_to_dma(struct wbsd_host *host, struct mmc_data *data)
{
	size_t len = 0;
	int i;

	for (i = 0; i < data->sg_len; i++)
		len += data->sg[i].length;
	sg_copy_to_buffer(data->sg, data->sg_len, host->dma_buffer, len);
}