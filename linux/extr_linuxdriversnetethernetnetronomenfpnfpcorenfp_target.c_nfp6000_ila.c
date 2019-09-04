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
 int target_rw (int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int nfp6000_ila(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 1,   0, P32);	/* read_check_error */
	AT(2, 0,   0, P32);	/* read_int */
	AT(3, 0, P32,   0);	/* write_int */
	default:
		return target_rw(cpp_id, P32, 48, 4);
	}
}