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
struct gsmi_buf {int /*<<< orphan*/  handle; scalar_t__ start; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ gsmi_dev ; 
 int /*<<< orphan*/  kfree (struct gsmi_buf*) ; 

__attribute__((used)) static void gsmi_buf_free(struct gsmi_buf *smibuf)
{
	if (smibuf) {
		if (smibuf->start)
			dma_pool_free(gsmi_dev.dma_pool, smibuf->start,
				      smibuf->handle);
		kfree(smibuf);
	}
}