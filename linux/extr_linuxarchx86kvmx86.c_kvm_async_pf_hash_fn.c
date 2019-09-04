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
typedef  int /*<<< orphan*/  u32 ;
typedef  int gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_PF_PER_VCPU ; 
 int /*<<< orphan*/  hash_32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  order_base_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 kvm_async_pf_hash_fn(gfn_t gfn)
{
	return hash_32(gfn & 0xffffffff, order_base_2(ASYNC_PF_PER_VCPU));
}