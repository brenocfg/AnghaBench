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
typedef  int /*<<< orphan*/  u32 ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int CIM_MALA_SIZE ; 
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_cim_read_ma_la (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int cudbg_collect_cim_ma_la(struct cudbg_init *pdbg_init,
			    struct cudbg_buffer *dbg_buff,
			    struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	int size, rc;

	size = 2 * CIM_MALA_SIZE * 5 * sizeof(u32);
	rc = cudbg_get_buff(pdbg_init, dbg_buff, size, &temp_buff);
	if (rc)
		return rc;

	t4_cim_read_ma_la(padap,
			  (u32 *)temp_buff.data,
			  (u32 *)((char *)temp_buff.data +
				  5 * CIM_MALA_SIZE));
	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}