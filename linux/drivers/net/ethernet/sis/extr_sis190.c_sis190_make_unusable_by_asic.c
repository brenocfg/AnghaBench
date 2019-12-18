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
struct RxDesc {int PSize; int status; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int RingEnd ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void sis190_make_unusable_by_asic(struct RxDesc *desc)
{
	desc->PSize = 0x0;
	desc->addr = cpu_to_le32(0xdeadbeef);
	desc->size &= cpu_to_le32(RingEnd);
	wmb();
	desc->status = 0x0;
}