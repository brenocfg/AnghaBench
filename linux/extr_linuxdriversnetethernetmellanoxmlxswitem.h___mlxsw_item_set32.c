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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ bits; } ;
struct mlxsw_item {int shift; int /*<<< orphan*/  no_real_shift; TYPE_1__ size; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int __mlxsw_item_offset (struct mlxsw_item const*,unsigned short,int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static inline void __mlxsw_item_set32(char *buf, const struct mlxsw_item *item,
				      unsigned short index, u32 val)
{
	unsigned int offset = __mlxsw_item_offset(item, index,
						  sizeof(u32));
	__be32 *b = (__be32 *) buf;
	u32 mask = GENMASK(item->size.bits - 1, 0) << item->shift;
	u32 tmp;

	if (!item->no_real_shift)
		val <<= item->shift;
	val &= mask;
	tmp = be32_to_cpu(b[offset]);
	tmp &= ~mask;
	tmp |= val;
	b[offset] = cpu_to_be32(tmp);
}