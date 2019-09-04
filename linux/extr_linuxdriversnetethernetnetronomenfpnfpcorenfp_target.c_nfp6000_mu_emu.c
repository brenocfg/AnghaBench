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
 int nfp6000_mu_common (int) ; 

__attribute__((used)) static int nfp6000_mu_emu(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(18, 0,   0, P32);	/* read_queue */
	AT(18, 1,   0, P32);	/* read_queue_ring */
	AT(18, 2, P32,   0);	/* write_queue */
	AT(18, 3, P32,   0);	/* write_queue_ring */
	AT(20, 2, P32,   0);	/* journal */
	AT(21, 0,   0, P32);	/* get */
	AT(21, 1,   0, P32);	/* get_eop */
	AT(21, 2,   0, P32);	/* get_freely */
	AT(22, 0,   0, P32);	/* pop */
	AT(22, 1,   0, P32);	/* pop_eop */
	AT(22, 2,   0, P32);	/* pop_freely */
	default:
		return nfp6000_mu_common(cpp_id);
	}
}