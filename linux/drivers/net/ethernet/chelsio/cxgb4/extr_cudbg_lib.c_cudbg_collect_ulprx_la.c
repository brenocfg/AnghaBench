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
struct cudbg_ulprx_la {int /*<<< orphan*/  size; scalar_t__ data; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULPRX_LA_SIZE ; 
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_ulprx_read_la (struct adapter*,int /*<<< orphan*/ *) ; 

int cudbg_collect_ulprx_la(struct cudbg_init *pdbg_init,
			   struct cudbg_buffer *dbg_buff,
			   struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	struct cudbg_ulprx_la *ulprx_la_buff;
	int rc;

	rc = cudbg_get_buff(pdbg_init, dbg_buff, sizeof(struct cudbg_ulprx_la),
			    &temp_buff);
	if (rc)
		return rc;

	ulprx_la_buff = (struct cudbg_ulprx_la *)temp_buff.data;
	t4_ulprx_read_la(padap, (u32 *)ulprx_la_buff->data);
	ulprx_la_buff->size = ULPRX_LA_SIZE;
	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}