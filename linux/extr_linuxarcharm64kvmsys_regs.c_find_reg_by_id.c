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
typedef  int /*<<< orphan*/  u64 ;
struct sys_reg_params {int dummy; } ;
struct sys_reg_desc {int dummy; } ;

/* Variables and functions */
 struct sys_reg_desc const* find_reg (struct sys_reg_params*,struct sys_reg_desc const*,unsigned int) ; 
 int /*<<< orphan*/  index_to_params (int /*<<< orphan*/ ,struct sys_reg_params*) ; 

const struct sys_reg_desc *find_reg_by_id(u64 id,
					  struct sys_reg_params *params,
					  const struct sys_reg_desc table[],
					  unsigned int num)
{
	if (!index_to_params(id, params))
		return NULL;

	return find_reg(params, table, num);
}