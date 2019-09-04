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

/* Variables and functions */
 int BTE_WACQUIRE ; 
 int BTE_ZERO_FILL ; 
 int /*<<< orphan*/  FETCHOP_LOAD ; 
 int /*<<< orphan*/  FETCHOP_LOAD_OP (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FETCHOP_VAR_SIZE ; 
 int SH2_AMO_CACHE_ENTRIES ; 
 scalar_t__ TO_AMO (int /*<<< orphan*/ ) ; 
 unsigned long __IA64_UNCACHED_OFFSET ; 
 int /*<<< orphan*/  __pa (unsigned long) ; 
 int bte_copy (int /*<<< orphan*/ ,unsigned long,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_node_number (int /*<<< orphan*/ ) ; 
 scalar_t__ is_shub2 () ; 
 scalar_t__ is_sn2 ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int nasid_to_cnodeid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scratch_page ; 

__attribute__((used)) static inline int
mspec_zero_block(unsigned long addr, int len)
{
	int status;

	if (is_sn2) {
		if (is_shub2()) {
			int nid;
			void *p;
			int i;

			nid = nasid_to_cnodeid(get_node_number(__pa(addr)));
			p = (void *)TO_AMO(scratch_page[nid]);

			for (i=0; i < SH2_AMO_CACHE_ENTRIES; i++) {
				FETCHOP_LOAD_OP(p, FETCHOP_LOAD);
				p += FETCHOP_VAR_SIZE;
			}
		}

		status = bte_copy(0, addr & ~__IA64_UNCACHED_OFFSET, len,
				  BTE_WACQUIRE | BTE_ZERO_FILL, NULL);
	} else {
		memset((char *) addr, 0, len);
		status = 0;
	}
	return status;
}