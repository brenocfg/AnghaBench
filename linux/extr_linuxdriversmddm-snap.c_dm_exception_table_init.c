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
typedef  int uint32_t ;
struct list_head {int dummy; } ;
struct dm_exception_table {unsigned int hash_shift; int hash_mask; scalar_t__ table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (scalar_t__) ; 
 scalar_t__ dm_vcalloc (int,int) ; 

__attribute__((used)) static int dm_exception_table_init(struct dm_exception_table *et,
				   uint32_t size, unsigned hash_shift)
{
	unsigned int i;

	et->hash_shift = hash_shift;
	et->hash_mask = size - 1;
	et->table = dm_vcalloc(size, sizeof(struct list_head));
	if (!et->table)
		return -ENOMEM;

	for (i = 0; i < size; i++)
		INIT_LIST_HEAD(et->table + i);

	return 0;
}