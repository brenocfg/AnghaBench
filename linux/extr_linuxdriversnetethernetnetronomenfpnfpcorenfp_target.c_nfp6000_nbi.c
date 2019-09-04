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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int nfp6000_nbi_dma (int /*<<< orphan*/ ) ; 
 int nfp6000_nbi_ppc (int /*<<< orphan*/ ) ; 
 int nfp6000_nbi_stats (int /*<<< orphan*/ ) ; 
 int nfp6000_nbi_tm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp6000_nbi(u32 cpp_id, u64 address)
{
	u64 rel_addr = address & 0x3fFFFF;

	if (rel_addr < (1 << 20))
		return nfp6000_nbi_dma(cpp_id);
	if (rel_addr < (2 << 20))
		return nfp6000_nbi_stats(cpp_id);
	if (rel_addr < (3 << 20))
		return nfp6000_nbi_tm(cpp_id);
	return nfp6000_nbi_ppc(cpp_id);
}