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
struct uasm_reloc {int lab; int /*<<< orphan*/  type; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_MIPS_PC16 ; 

void uasm_r_mips_pc16(struct uasm_reloc **rel, u32 *addr, int lid)
{
	(*rel)->addr = addr;
	(*rel)->type = R_MIPS_PC16;
	(*rel)->lab = lid;
	(*rel)++;
}