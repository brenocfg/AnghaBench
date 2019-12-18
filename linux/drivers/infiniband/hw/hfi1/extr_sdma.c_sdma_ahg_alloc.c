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
struct sdma_engine {int /*<<< orphan*/  ahg_bits; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int ffz (int /*<<< orphan*/ ) ; 
 int test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_hfi1_ahg_allocate (struct sdma_engine*,int) ; 

int sdma_ahg_alloc(struct sdma_engine *sde)
{
	int nr;
	int oldbit;

	if (!sde) {
		trace_hfi1_ahg_allocate(sde, -EINVAL);
		return -EINVAL;
	}
	while (1) {
		nr = ffz(READ_ONCE(sde->ahg_bits));
		if (nr > 31) {
			trace_hfi1_ahg_allocate(sde, -ENOSPC);
			return -ENOSPC;
		}
		oldbit = test_and_set_bit(nr, &sde->ahg_bits);
		if (!oldbit)
			break;
		cpu_relax();
	}
	trace_hfi1_ahg_allocate(sde, nr);
	return nr;
}