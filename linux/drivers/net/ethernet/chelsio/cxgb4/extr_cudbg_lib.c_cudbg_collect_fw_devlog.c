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
struct devlog_params {scalar_t__ start; int /*<<< orphan*/  size; int /*<<< orphan*/  memtype; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int sys_err; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  drv_memwin; struct devlog_params devlog; } ;
struct adapter {int /*<<< orphan*/  win0_lock; TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int /*<<< orphan*/ ,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  cudbg_put_buff (struct cudbg_init*,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int t4_init_devlog_params (struct adapter*) ; 
 int t4_memory_rw (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int cudbg_collect_fw_devlog(struct cudbg_init *pdbg_init,
			    struct cudbg_buffer *dbg_buff,
			    struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	struct devlog_params *dparams;
	int rc = 0;

	rc = t4_init_devlog_params(padap);
	if (rc < 0) {
		cudbg_err->sys_err = rc;
		return rc;
	}

	dparams = &padap->params.devlog;
	rc = cudbg_get_buff(pdbg_init, dbg_buff, dparams->size, &temp_buff);
	if (rc)
		return rc;

	/* Collect FW devlog */
	if (dparams->start != 0) {
		spin_lock(&padap->win0_lock);
		rc = t4_memory_rw(padap, padap->params.drv_memwin,
				  dparams->memtype, dparams->start,
				  dparams->size,
				  (__be32 *)(char *)temp_buff.data,
				  1);
		spin_unlock(&padap->win0_lock);
		if (rc) {
			cudbg_err->sys_err = rc;
			cudbg_put_buff(pdbg_init, &temp_buff);
			return rc;
		}
	}
	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}