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
typedef  int u8 ;
struct chash_table {int /*<<< orphan*/  data; int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  __CHASH_DATA_SIZE (int,int,unsigned int) ; 
 int /*<<< orphan*/  __CHASH_TABLE_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int chash_table_alloc(struct chash_table *table, u8 bits, u8 key_size,
		      unsigned int value_size, gfp_t gfp_mask)
{
	if (bits > 31)
		return -EINVAL;

	if (key_size != 4 && key_size != 8)
		return -EINVAL;

	table->data = kcalloc(__CHASH_DATA_SIZE(bits, key_size, value_size),
		       sizeof(long), gfp_mask);
	if (!table->data)
		return -ENOMEM;

	__CHASH_TABLE_INIT(table->table, table->data,
			   bits, key_size, value_size);

	return 0;
}