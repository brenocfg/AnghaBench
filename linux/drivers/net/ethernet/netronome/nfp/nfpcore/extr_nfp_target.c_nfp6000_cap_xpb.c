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
 int NFP_CPP_ACTION_RW ; 
 int NFP_CPP_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P32 ; 
 int target_rw (int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int nfp6000_cap_xpb(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 1,   0, P32); /* RingGet */
	AT(0, 2, P32,   0); /* Interthread Signal */
	AT(1, 1, P32,   0); /* RingPut */
	AT(1, 2, P32,   0); /* CTNNWr */
	AT(2, 0,   0, P32); /* ReflectRd, signal none */
	AT(2, 1,   0, P32); /* ReflectRd, signal self */
	AT(2, 2,   0, P32); /* ReflectRd, signal remote */
	AT(2, 3,   0, P32); /* ReflectRd, signal both */
	AT(3, 0, P32,   0); /* ReflectWr, signal none */
	AT(3, 1, P32,   0); /* ReflectWr, signal self */
	AT(3, 2, P32,   0); /* ReflectWr, signal remote */
	AT(3, 3, P32,   0); /* ReflectWr, signal both */
	AT(NFP_CPP_ACTION_RW, 1, P32, P32);
	default:
		return target_rw(cpp_id, P32, 1, 63);
	}
}