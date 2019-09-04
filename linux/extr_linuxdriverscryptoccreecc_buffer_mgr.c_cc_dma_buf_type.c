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
typedef  enum cc_req_dma_buf_type { ____Placeholder_cc_req_dma_buf_type } cc_req_dma_buf_type ;

/* Variables and functions */
#define  CC_DMA_BUF_DLLI 130 
#define  CC_DMA_BUF_MLLI 129 
#define  CC_DMA_BUF_NULL 128 

__attribute__((used)) static inline char *cc_dma_buf_type(enum cc_req_dma_buf_type type)
{
	switch (type) {
	case CC_DMA_BUF_NULL:
		return "BUF_NULL";
	case CC_DMA_BUF_DLLI:
		return "BUF_DLLI";
	case CC_DMA_BUF_MLLI:
		return "BUF_MLLI";
	default:
		return "BUF_INVALID";
	}
}