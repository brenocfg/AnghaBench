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
typedef  enum mcam_buffer_mode { ____Placeholder_mcam_buffer_mode } mcam_buffer_mode ;

/* Variables and functions */

__attribute__((used)) static inline int mcam_buffer_mode_supported(enum mcam_buffer_mode mode)
{
	switch (mode) {
#ifdef MCAM_MODE_VMALLOC
	case B_vmalloc:
#endif
#ifdef MCAM_MODE_DMA_CONTIG
	case B_DMA_contig:
#endif
#ifdef MCAM_MODE_DMA_SG
	case B_DMA_sg:
#endif
		return 1;
	default:
		return 0;
	}
}