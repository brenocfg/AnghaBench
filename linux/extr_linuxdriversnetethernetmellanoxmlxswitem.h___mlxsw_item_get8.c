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
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ bits; } ;
struct mlxsw_item {int shift; scalar_t__ no_real_shift; TYPE_1__ size; } ;

/* Variables and functions */
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int __mlxsw_item_offset (struct mlxsw_item const*,unsigned short,int) ; 

__attribute__((used)) static inline u8 __mlxsw_item_get8(const char *buf,
				   const struct mlxsw_item *item,
				   unsigned short index)
{
	unsigned int offset = __mlxsw_item_offset(item, index, sizeof(u8));
	u8 *b = (u8 *) buf;
	u8 tmp;

	tmp = b[offset];
	tmp >>= item->shift;
	tmp &= GENMASK(item->size.bits - 1, 0);
	if (item->no_real_shift)
		tmp <<= item->shift;
	return tmp;
}