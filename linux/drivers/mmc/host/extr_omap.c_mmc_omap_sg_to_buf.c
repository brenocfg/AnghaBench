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
struct scatterlist {int /*<<< orphan*/  length; } ;
struct mmc_omap_host {int sg_idx; int /*<<< orphan*/  total_bytes_left; int /*<<< orphan*/  buffer_bytes_left; int /*<<< orphan*/  buffer; TYPE_1__* data; } ;
struct TYPE_2__ {struct scatterlist* sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 

__attribute__((used)) static void
mmc_omap_sg_to_buf(struct mmc_omap_host *host)
{
	struct scatterlist *sg;

	sg = host->data->sg + host->sg_idx;
	host->buffer_bytes_left = sg->length;
	host->buffer = sg_virt(sg);
	if (host->buffer_bytes_left > host->total_bytes_left)
		host->buffer_bytes_left = host->total_bytes_left;
}