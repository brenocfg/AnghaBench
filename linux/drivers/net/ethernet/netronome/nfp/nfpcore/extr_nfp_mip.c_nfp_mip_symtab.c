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
struct nfp_mip {int /*<<< orphan*/  symtab_size; int /*<<< orphan*/  symtab_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

void nfp_mip_symtab(const struct nfp_mip *mip, u32 *addr, u32 *size)
{
	*addr = le32_to_cpu(mip->symtab_addr);
	*size = le32_to_cpu(mip->symtab_size);
}