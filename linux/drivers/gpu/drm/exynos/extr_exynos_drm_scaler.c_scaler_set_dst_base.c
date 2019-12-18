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
struct scaler_context {int dummy; } ;
struct exynos_drm_ipp_buffer {int /*<<< orphan*/ * dma_addr; TYPE_1__* format; } ;
struct TYPE_2__ {int num_planes; } ;

/* Variables and functions */
#define  SCALER_DST_CB_BASE 130 
#define  SCALER_DST_CR_BASE 129 
#define  SCALER_DST_Y_BASE 128 
 int /*<<< orphan*/  scaler_write (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void scaler_set_dst_base(struct scaler_context *scaler,
	struct exynos_drm_ipp_buffer *dst_buf)
{
	static unsigned int bases[] = {
		SCALER_DST_Y_BASE,
		SCALER_DST_CB_BASE,
		SCALER_DST_CR_BASE,
	};
	int i;

	for (i = 0; i < dst_buf->format->num_planes; ++i)
		scaler_write(dst_buf->dma_addr[i], bases[i]);
}