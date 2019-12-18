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
struct radeon_device {int /*<<< orphan*/  smc_idx_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_IND_DATA_0 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int ci_set_smc_sram_address (struct radeon_device*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ci_copy_bytes_to_smc(struct radeon_device *rdev,
			 u32 smc_start_address,
			 const u8 *src, u32 byte_count, u32 limit)
{
	unsigned long flags;
	u32 data, original_data;
	u32 addr;
	u32 extra_shift;
	int ret = 0;

	if (smc_start_address & 3)
		return -EINVAL;
	if ((smc_start_address + byte_count) > limit)
		return -EINVAL;

	addr = smc_start_address;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	while (byte_count >= 4) {
		/* SMC address space is BE */
		data = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];

		ret = ci_set_smc_sram_address(rdev, addr, limit);
		if (ret)
			goto done;

		WREG32(SMC_IND_DATA_0, data);

		src += 4;
		byte_count -= 4;
		addr += 4;
	}

	/* RMW for the final bytes */
	if (byte_count > 0) {
		data = 0;

		ret = ci_set_smc_sram_address(rdev, addr, limit);
		if (ret)
			goto done;

		original_data = RREG32(SMC_IND_DATA_0);

		extra_shift = 8 * (4 - byte_count);

		while (byte_count > 0) {
			data = (data << 8) + *src++;
			byte_count--;
		}

		data <<= extra_shift;

		data |= (original_data & ~((~0UL) << extra_shift));

		ret = ci_set_smc_sram_address(rdev, addr, limit);
		if (ret)
			goto done;

		WREG32(SMC_IND_DATA_0, data);
	}

done:
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);

	return ret;
}