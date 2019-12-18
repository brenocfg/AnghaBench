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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAYMAN_SYSLS_DISABLE_LENGTH ; 
 int /*<<< orphan*/  CAYMAN_SYSLS_ENABLE_LENGTH ; 
 int /*<<< orphan*/  btc_program_mgcg_hw_sequence (struct radeon_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cayman_sysls_disable ; 
 int /*<<< orphan*/  cayman_sysls_enable ; 

__attribute__((used)) static void ni_ls_clockgating_enable(struct radeon_device *rdev,
				     bool enable)
{
	u32 count;
	const u32 *ps = NULL;

	if (enable) {
		ps = (const u32 *)&cayman_sysls_enable;
		count = CAYMAN_SYSLS_ENABLE_LENGTH;
	} else {
		ps = (const u32 *)&cayman_sysls_disable;
		count = CAYMAN_SYSLS_DISABLE_LENGTH;
	}

	btc_program_mgcg_hw_sequence(rdev, ps, count);

}