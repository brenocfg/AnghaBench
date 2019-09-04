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
struct npu {int mmio_atsd_count; int /*<<< orphan*/  mmio_atsd_usage; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_mmio_atsd_reg(struct npu *npu)
{
	int i;

	for (i = 0; i < npu->mmio_atsd_count; i++) {
		if (!test_bit(i, &npu->mmio_atsd_usage))
			if (!test_and_set_bit_lock(i, &npu->mmio_atsd_usage))
				return i;
	}

	return -ENOSPC;
}