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
typedef  unsigned int u32 ;
struct mlxsw_sp2_kvdl_part {unsigned int indexes_per_usage_bit; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int mlxsw_sp2_kvdl_part_find_zero_bits (struct mlxsw_sp2_kvdl_part*,unsigned int,unsigned int*) ; 

__attribute__((used)) static int mlxsw_sp2_kvdl_part_alloc(struct mlxsw_sp2_kvdl_part *part,
				     unsigned int size,
				     u32 *p_kvdl_index)
{
	unsigned int bit_count;
	unsigned int bit;
	unsigned int i;
	int err;

	bit_count = DIV_ROUND_UP(size, part->indexes_per_usage_bit);
	err = mlxsw_sp2_kvdl_part_find_zero_bits(part, bit_count, &bit);
	if (err)
		return err;
	for (i = 0; i < bit_count; i++)
		__set_bit(bit + i, part->usage);
	*p_kvdl_index = bit * part->indexes_per_usage_bit;
	return 0;
}