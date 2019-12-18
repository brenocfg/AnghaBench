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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AT (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NFP_CPP_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P32 ; 
 int target_rw (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nfp6000_cls(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 3, P32,  0); /* xor */
	AT(2, 0, P32,  0); /* set */
	AT(2, 1, P32,  0); /* clr */
	AT(4, 0, P32,  0); /* add */
	AT(4, 1, P32,  0); /* add64 */
	AT(6, 0, P32,  0); /* sub */
	AT(6, 1, P32,  0); /* sub64 */
	AT(6, 2, P32,  0); /* subsat */
	AT(8, 2, P32,  0); /* hash_mask */
	AT(8, 3, P32,  0); /* hash_clear */
	AT(9, 0,  0, P32); /* ring_get */
	AT(9, 1,  0, P32); /* ring_pop */
	AT(9, 2,  0, P32); /* ring_get_freely */
	AT(9, 3,  0, P32); /* ring_pop_freely */
	AT(10, 0, P32,  0); /* ring_put */
	AT(10, 2, P32,  0); /* ring_journal */
	AT(14, 0,  P32, 0); /* reflect_write_sig_local */
	AT(15, 1,  0, P32); /* reflect_read_sig_local */
	AT(17, 2, P32,  0); /* statisic */
	AT(24, 0,  0, P32); /* ring_read */
	AT(24, 1, P32,  0); /* ring_write */
	AT(25, 0,  0, P32); /* ring_workq_add_thread */
	AT(25, 1, P32,  0); /* ring_workq_add_work */
	default:
		return target_rw(cpp_id, P32, 0, 64);
	}
}