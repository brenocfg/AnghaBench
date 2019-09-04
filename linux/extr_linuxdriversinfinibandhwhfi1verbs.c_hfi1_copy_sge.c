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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rvt_sge {scalar_t__ vaddr; } ;
struct rvt_sge_state {struct rvt_sge sge; } ;

/* Variables and functions */
 scalar_t__ COPY_ADAPTIVE ; 
 scalar_t__ COPY_CACHELESS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cacheless_memcpy (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int) ; 
 int rvt_get_sge_length (struct rvt_sge*,int) ; 
 int /*<<< orphan*/  rvt_update_sge (struct rvt_sge_state*,int,int) ; 
 scalar_t__ sge_copy_mode ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wss_advance_clean_counter () ; 
 int wss_exceeds_threshold () ; 
 int /*<<< orphan*/  wss_insert (scalar_t__) ; 

void hfi1_copy_sge(
	struct rvt_sge_state *ss,
	void *data, u32 length,
	bool release,
	bool copy_last)
{
	struct rvt_sge *sge = &ss->sge;
	int i;
	bool in_last = false;
	bool cacheless_copy = false;

	if (sge_copy_mode == COPY_CACHELESS) {
		cacheless_copy = length >= PAGE_SIZE;
	} else if (sge_copy_mode == COPY_ADAPTIVE) {
		if (length >= PAGE_SIZE) {
			/*
			 * NOTE: this *assumes*:
			 * o The first vaddr is the dest.
			 * o If multiple pages, then vaddr is sequential.
			 */
			wss_insert(sge->vaddr);
			if (length >= (2 * PAGE_SIZE))
				wss_insert(sge->vaddr + PAGE_SIZE);

			cacheless_copy = wss_exceeds_threshold();
		} else {
			wss_advance_clean_counter();
		}
	}
	if (copy_last) {
		if (length > 8) {
			length -= 8;
		} else {
			copy_last = false;
			in_last = true;
		}
	}

again:
	while (length) {
		u32 len = rvt_get_sge_length(sge, length);

		WARN_ON_ONCE(len == 0);
		if (unlikely(in_last)) {
			/* enforce byte transfer ordering */
			for (i = 0; i < len; i++)
				((u8 *)sge->vaddr)[i] = ((u8 *)data)[i];
		} else if (cacheless_copy) {
			cacheless_memcpy(sge->vaddr, data, len);
		} else {
			memcpy(sge->vaddr, data, len);
		}
		rvt_update_sge(ss, len, release);
		data += len;
		length -= len;
	}

	if (copy_last) {
		copy_last = false;
		in_last = true;
		length = 8;
		goto again;
	}
}