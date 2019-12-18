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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int global_mmio_size; } ;
struct ocxl_afu {scalar_t__ global_mmio_ptr; TYPE_1__ config; } ;
typedef  enum ocxl_endian { ____Placeholder_ocxl_endian } ocxl_endian ;

/* Variables and functions */
 int EINVAL ; 
#define  OCXL_BIG_ENDIAN 128 
 int OCXL_HOST_ENDIAN ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writeq_be (int /*<<< orphan*/ ,char*) ; 

int ocxl_global_mmio_write64(struct ocxl_afu *afu, size_t offset,
				enum ocxl_endian endian, u64 val)
{
	if (offset > afu->config.global_mmio_size - 8)
		return -EINVAL;

#ifdef __BIG_ENDIAN__
	if (endian == OCXL_HOST_ENDIAN)
		endian = OCXL_BIG_ENDIAN;
#endif

	switch (endian) {
	case OCXL_BIG_ENDIAN:
		writeq_be(val, (char *)afu->global_mmio_ptr + offset);
		break;

	default:
		writeq(val, (char *)afu->global_mmio_ptr + offset);
		break;
	}


	return 0;
}