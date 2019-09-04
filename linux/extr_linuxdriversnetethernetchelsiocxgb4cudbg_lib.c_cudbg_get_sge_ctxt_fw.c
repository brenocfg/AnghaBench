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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct cudbg_init {int dummy; } ;
struct cudbg_ch_cntxt {scalar_t__ cntxt_id; void* cntxt_type; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 void* CTXT_CNM ; 
 void* CTXT_FLM ; 
 int /*<<< orphan*/  cudbg_read_sge_ctxt (struct cudbg_init*,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int cudbg_sge_ctxt_check_valid (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void cudbg_get_sge_ctxt_fw(struct cudbg_init *pdbg_init, u32 max_qid,
				  u8 ctxt_type,
				  struct cudbg_ch_cntxt **out_buff)
{
	struct cudbg_ch_cntxt *buff = *out_buff;
	int rc;
	u32 j;

	for (j = 0; j < max_qid; j++) {
		cudbg_read_sge_ctxt(pdbg_init, j, ctxt_type, buff->data);
		rc = cudbg_sge_ctxt_check_valid(buff->data, ctxt_type);
		if (!rc)
			continue;

		buff->cntxt_type = ctxt_type;
		buff->cntxt_id = j;
		buff++;
		if (ctxt_type == CTXT_FLM) {
			cudbg_read_sge_ctxt(pdbg_init, j, CTXT_CNM, buff->data);
			buff->cntxt_type = CTXT_CNM;
			buff->cntxt_id = j;
			buff++;
		}
	}

	*out_buff = buff;
}