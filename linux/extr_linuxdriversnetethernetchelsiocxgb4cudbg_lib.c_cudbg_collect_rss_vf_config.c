#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cudbg_rss_vf_conf {int /*<<< orphan*/  rss_vf_vfh; int /*<<< orphan*/  rss_vf_vfl; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int vfcount; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_read_rss_vf_config (struct adapter*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int cudbg_collect_rss_vf_config(struct cudbg_init *pdbg_init,
				struct cudbg_buffer *dbg_buff,
				struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	struct cudbg_rss_vf_conf *vfconf;
	int vf, rc, vf_count;

	vf_count = padap->params.arch.vfcount;
	rc = cudbg_get_buff(pdbg_init, dbg_buff,
			    vf_count * sizeof(struct cudbg_rss_vf_conf),
			    &temp_buff);
	if (rc)
		return rc;

	vfconf = (struct cudbg_rss_vf_conf *)temp_buff.data;
	for (vf = 0; vf < vf_count; vf++)
		t4_read_rss_vf_config(padap, vf, &vfconf[vf].rss_vf_vfl,
				      &vfconf[vf].rss_vf_vfh, true);
	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}