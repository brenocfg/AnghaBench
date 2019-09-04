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
struct cudbg_ver_hdr {int size; int /*<<< orphan*/  revision; int /*<<< orphan*/  signature; } ;
struct cudbg_meminfo {int dummy; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int sys_err; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUDBG_ENTITY_SIGNATURE ; 
 int /*<<< orphan*/  CUDBG_MEMINFO_REV ; 
 int cudbg_fill_meminfo (struct adapter*,struct cudbg_meminfo*) ; 
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  cudbg_put_buff (struct cudbg_init*,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 

int cudbg_collect_meminfo(struct cudbg_init *pdbg_init,
			  struct cudbg_buffer *dbg_buff,
			  struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	struct cudbg_meminfo *meminfo_buff;
	struct cudbg_ver_hdr *ver_hdr;
	int rc;

	rc = cudbg_get_buff(pdbg_init, dbg_buff,
			    sizeof(struct cudbg_ver_hdr) +
			    sizeof(struct cudbg_meminfo),
			    &temp_buff);
	if (rc)
		return rc;

	ver_hdr = (struct cudbg_ver_hdr *)temp_buff.data;
	ver_hdr->signature = CUDBG_ENTITY_SIGNATURE;
	ver_hdr->revision = CUDBG_MEMINFO_REV;
	ver_hdr->size = sizeof(struct cudbg_meminfo);

	meminfo_buff = (struct cudbg_meminfo *)(temp_buff.data +
						sizeof(*ver_hdr));
	rc = cudbg_fill_meminfo(padap, meminfo_buff);
	if (rc) {
		cudbg_err->sys_err = rc;
		cudbg_put_buff(pdbg_init, &temp_buff);
		return rc;
	}

	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}