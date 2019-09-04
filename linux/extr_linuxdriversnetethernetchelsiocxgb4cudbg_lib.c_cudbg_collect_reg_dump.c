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
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {int /*<<< orphan*/  size; scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  T4_REGMAP_SIZE ; 
 int /*<<< orphan*/  T5_REGMAP_SIZE ; 
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int /*<<< orphan*/ ,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_get_regs (struct adapter*,void*,int /*<<< orphan*/ ) ; 

int cudbg_collect_reg_dump(struct cudbg_init *pdbg_init,
			   struct cudbg_buffer *dbg_buff,
			   struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	u32 buf_size = 0;
	int rc = 0;

	if (is_t4(padap->params.chip))
		buf_size = T4_REGMAP_SIZE;
	else if (is_t5(padap->params.chip) || is_t6(padap->params.chip))
		buf_size = T5_REGMAP_SIZE;

	rc = cudbg_get_buff(pdbg_init, dbg_buff, buf_size, &temp_buff);
	if (rc)
		return rc;
	t4_get_regs(padap, (void *)temp_buff.data, temp_buff.size);
	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}