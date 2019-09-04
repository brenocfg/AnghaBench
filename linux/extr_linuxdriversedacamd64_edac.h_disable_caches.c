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
 int X86_CR0_CD ; 
 int read_cr0 () ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  write_cr0 (int) ; 

__attribute__((used)) static inline void disable_caches(void *dummy)
{
	write_cr0(read_cr0() | X86_CR0_CD);
	wbinvd();
}