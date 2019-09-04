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
typedef  int /*<<< orphan*/  u32 ;
struct gsc_context {int dummy; } ;
struct exynos_drm_ipp_buffer {int /*<<< orphan*/ * dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSC_IN_BASE_ADDR_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_IN_BASE_ADDR_CR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_IN_BASE_ADDR_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_src_set_buf_seq (struct gsc_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gsc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsc_src_set_addr(struct gsc_context *ctx, u32 buf_id,
			    struct exynos_drm_ipp_buffer *buf)
{
	/* address register set */
	gsc_write(buf->dma_addr[0], GSC_IN_BASE_ADDR_Y(buf_id));
	gsc_write(buf->dma_addr[1], GSC_IN_BASE_ADDR_CB(buf_id));
	gsc_write(buf->dma_addr[2], GSC_IN_BASE_ADDR_CR(buf_id));

	gsc_src_set_buf_seq(ctx, buf_id, true);
}