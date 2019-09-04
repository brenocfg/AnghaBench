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
struct mlxsw_item {int dummy; } ;

/* Variables and functions */
 unsigned int __mlxsw_item_offset (struct mlxsw_item const*,unsigned short,int) ; 

__attribute__((used)) static inline char *__mlxsw_item_data(char *buf, const struct mlxsw_item *item,
				      unsigned short index)
{
	unsigned int offset = __mlxsw_item_offset(item, index, sizeof(char));

	return &buf[offset];
}