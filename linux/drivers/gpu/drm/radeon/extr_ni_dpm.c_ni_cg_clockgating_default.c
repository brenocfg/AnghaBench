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
 int /*<<< orphan*/  CAYMAN_CGCG_CGLS_DEFAULT_LENGTH ; 
 int /*<<< orphan*/  btc_program_mgcg_hw_sequence (struct radeon_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cayman_cgcg_cgls_default ; 

__attribute__((used)) static void ni_cg_clockgating_default(struct radeon_device *rdev)
{
	u32 count;
	const u32 *ps = NULL;

	ps = (const u32 *)&cayman_cgcg_cgls_default;
	count = CAYMAN_CGCG_CGLS_DEFAULT_LENGTH;

	btc_program_mgcg_hw_sequence(rdev, ps, count);
}