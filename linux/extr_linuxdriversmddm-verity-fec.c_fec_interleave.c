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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct dm_verity {int data_dev_block_bits; TYPE_1__* fec; } ;
struct TYPE_2__ {int rounds; int /*<<< orphan*/  rsn; } ;

/* Variables and functions */
 int do_div (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 fec_interleave(struct dm_verity *v, u64 offset)
{
	u32 mod;

	mod = do_div(offset, v->fec->rsn);
	return offset + mod * (v->fec->rounds << v->data_dev_block_bits);
}