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
struct TYPE_2__ {int /*<<< orphan*/  bytes; } ;
struct mlxsw_item {TYPE_1__ size; } ;

/* Variables and functions */
 unsigned int __mlxsw_item_offset (struct mlxsw_item const*,unsigned short,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __mlxsw_item_memcpy_to(char *buf, const char *src,
					  const struct mlxsw_item *item,
					  unsigned short index)
{
	unsigned int offset = __mlxsw_item_offset(item, index, sizeof(char));

	memcpy(&buf[offset], src, item->size.bytes);
}