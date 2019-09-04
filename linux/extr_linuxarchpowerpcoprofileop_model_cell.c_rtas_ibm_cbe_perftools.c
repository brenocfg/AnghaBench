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
typedef  int u64 ;

/* Variables and functions */
 int __pa (void*) ; 
 int /*<<< orphan*/  pm_rtas_token ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int,int,int,unsigned long) ; 

__attribute__((used)) static int
rtas_ibm_cbe_perftools(int subfunc, int passthru,
		       void *address, unsigned long length)
{
	u64 paddr = __pa(address);

	return rtas_call(pm_rtas_token, 5, 1, NULL, subfunc,
			 passthru, paddr >> 32, paddr & 0xffffffff, length);
}