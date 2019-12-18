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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int global_mmio_size; } ;
struct ocxl_afu {scalar_t__ global_mmio_ptr; TYPE_1__ config; } ;
typedef  enum ocxl_endian { ____Placeholder_ocxl_endian } ocxl_endian ;

/* Variables and functions */
 int EINVAL ; 
#define  OCXL_BIG_ENDIAN 128 
 int OCXL_HOST_ENDIAN ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writel_be (int /*<<< orphan*/ ,char*) ; 

int ocxl_global_mmio_write32(struct ocxl_afu *afu, size_t offset,
				enum ocxl_endian endian, u32 val)
{
	if (offset > afu->config.global_mmio_size - 4)
		return -EINVAL;

#ifdef __BIG_ENDIAN__
	if (endian == OCXL_HOST_ENDIAN)
		endian = OCXL_BIG_ENDIAN;
#endif

	switch (endian) {
	case OCXL_BIG_ENDIAN:
		writel_be(val, (char *)afu->global_mmio_ptr + offset);
		break;

	default:
		writel(val, (char *)afu->global_mmio_ptr + offset);
		break;
	}


	return 0;
}