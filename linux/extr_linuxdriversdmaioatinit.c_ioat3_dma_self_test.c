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
struct ioatdma_device {int dummy; } ;

/* Variables and functions */
 int ioat_dma_self_test (struct ioatdma_device*) ; 
 int ioat_xor_val_self_test (struct ioatdma_device*) ; 

__attribute__((used)) static int ioat3_dma_self_test(struct ioatdma_device *ioat_dma)
{
	int rc;

	rc = ioat_dma_self_test(ioat_dma);
	if (rc)
		return rc;

	rc = ioat_xor_val_self_test(ioat_dma);

	return rc;
}