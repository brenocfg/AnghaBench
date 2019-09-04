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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * ptr; } ;
struct radeon_cs_parser {TYPE_1__ ib; struct radeon_cs_chunk* chunk_ib; } ;
struct radeon_cs_chunk {int /*<<< orphan*/ * kdata; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 radeon_get_ib_value(struct radeon_cs_parser *p, int idx)
{
	struct radeon_cs_chunk *ibc = p->chunk_ib;

	if (ibc->kdata)
		return ibc->kdata[idx];
	return p->ib.ptr[idx];
}