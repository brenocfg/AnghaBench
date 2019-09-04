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
struct fsl_re_desc {int /*<<< orphan*/  async_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_cookie_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_descriptor_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_re_desc_done(struct fsl_re_desc *desc)
{
	dma_cookie_complete(&desc->async_tx);
	dma_descriptor_unmap(&desc->async_tx);
	dmaengine_desc_get_callback_invoke(&desc->async_tx, NULL);
}