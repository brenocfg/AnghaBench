#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {int addr; } ;
struct TYPE_3__ {scalar_t__ addr; } ;
struct h_epas {TYPE_2__ user; TYPE_1__ kernel; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ ioremap (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hcp_epas_ctor(struct h_epas *epas, u64 paddr_kernel,
				 u64 paddr_user)
{
	/* To support 64k pages we must round to 64k page boundary */
	epas->kernel.addr = ioremap((paddr_kernel & PAGE_MASK), PAGE_SIZE) +
			    (paddr_kernel & ~PAGE_MASK);
	epas->user.addr = paddr_user;
}