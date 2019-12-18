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
typedef  size_t u32 ;
struct cxgb4_collect_entity {int (* collect_cb ) (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_error*) ;int /*<<< orphan*/  entity; } ;
struct cudbg_init {int dummy; } ;
struct cudbg_error {int /*<<< orphan*/  sys_warn; scalar_t__ sys_err; int /*<<< orphan*/  member_0; } ;
struct cudbg_entity_hdr {size_t size; int hdr_flags; int /*<<< orphan*/  sys_warn; scalar_t__ sys_err; int /*<<< orphan*/  start_offset; int /*<<< orphan*/  entity_type; } ;
struct cudbg_buffer {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int CUDBG_SYSTEM_ERROR ; 
 int /*<<< orphan*/  cudbg_align_debug_buffer (struct cudbg_buffer*,struct cudbg_entity_hdr*) ; 
 struct cudbg_entity_hdr* cudbg_get_entity_hdr (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cudbg_error*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_error*) ; 

__attribute__((used)) static void cxgb4_cudbg_collect_entity(struct cudbg_init *pdbg_init,
				       struct cudbg_buffer *dbg_buff,
				       const struct cxgb4_collect_entity *e_arr,
				       u32 arr_size, void *buf, u32 *tot_size)
{
	struct cudbg_error cudbg_err = { 0 };
	struct cudbg_entity_hdr *entity_hdr;
	u32 i, total_size = 0;
	int ret;

	for (i = 0; i < arr_size; i++) {
		const struct cxgb4_collect_entity *e = &e_arr[i];

		entity_hdr = cudbg_get_entity_hdr(buf, e->entity);
		entity_hdr->entity_type = e->entity;
		entity_hdr->start_offset = dbg_buff->offset;
		memset(&cudbg_err, 0, sizeof(struct cudbg_error));
		ret = e->collect_cb(pdbg_init, dbg_buff, &cudbg_err);
		if (ret) {
			entity_hdr->size = 0;
			dbg_buff->offset = entity_hdr->start_offset;
		} else {
			cudbg_align_debug_buffer(dbg_buff, entity_hdr);
		}

		/* Log error and continue with next entity */
		if (cudbg_err.sys_err)
			ret = CUDBG_SYSTEM_ERROR;

		entity_hdr->hdr_flags = ret;
		entity_hdr->sys_err = cudbg_err.sys_err;
		entity_hdr->sys_warn = cudbg_err.sys_warn;
		total_size += entity_hdr->size;
	}

	*tot_size += total_size;
}