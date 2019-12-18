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
struct ipmmu_vmsa_device {unsigned int num_ctx; } ;

/* Variables and functions */
 scalar_t__ IMCTR ; 
 unsigned int IM_CTX_SIZE ; 
 int /*<<< orphan*/  ipmmu_write (struct ipmmu_vmsa_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipmmu_device_reset(struct ipmmu_vmsa_device *mmu)
{
	unsigned int i;

	/* Disable all contexts. */
	for (i = 0; i < mmu->num_ctx; ++i)
		ipmmu_write(mmu, i * IM_CTX_SIZE + IMCTR, 0);
}