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
typedef  int u8 ;
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FIRST_SMC_INT_VECT_REG ; 
 scalar_t__ SMC_ISR_FFD8_FFDB ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 

__attribute__((used)) static int rv770_program_interrupt_vectors(struct radeon_device *rdev,
					   u32 smc_first_vector, const u8 *src,
					   u32 byte_count)
{
	u32 tmp, i;

	if (byte_count % 4)
		return -EINVAL;

	if (smc_first_vector < FIRST_SMC_INT_VECT_REG) {
		tmp = FIRST_SMC_INT_VECT_REG - smc_first_vector;

		if (tmp > byte_count)
			return 0;

		byte_count -= tmp;
		src += tmp;
		smc_first_vector = FIRST_SMC_INT_VECT_REG;
	}

	for (i = 0; i < byte_count; i += 4) {
		/* SMC address space is BE */
		tmp = (src[i] << 24) | (src[i + 1] << 16) | (src[i + 2] << 8) | src[i + 3];

		WREG32(SMC_ISR_FFD8_FFDB + i, tmp);
	}

	return 0;
}