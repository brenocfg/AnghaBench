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
typedef  unsigned int u64 ;
struct sdma_engine {TYPE_1__* dd; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_CNT ; 
 int /*<<< orphan*/  DESC_CNT_CNT_MASK ; 
 int /*<<< orphan*/  DESC_CNT_CNT_SHIFT ; 
 int HFI1_HAS_SDMA_TIMEOUT ; 
 unsigned int SD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sde_csr (struct sdma_engine*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void sdma_set_desc_cnt(struct sdma_engine *sde, unsigned cnt)
{
	u64 reg;

	if (!(sde->dd->flags & HFI1_HAS_SDMA_TIMEOUT))
		return;
	reg = cnt;
	reg &= SD(DESC_CNT_CNT_MASK);
	reg <<= SD(DESC_CNT_CNT_SHIFT);
	write_sde_csr(sde, SD(DESC_CNT), reg);
}