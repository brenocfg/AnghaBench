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
typedef  enum aarch64_reloc_op { ____Placeholder_aarch64_reloc_op } aarch64_reloc_op ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
#define  RELOC_OP_ABS 131 
#define  RELOC_OP_NONE 130 
#define  RELOC_OP_PAGE 129 
#define  RELOC_OP_PREL 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static u64 do_reloc(enum aarch64_reloc_op reloc_op, __le32 *place, u64 val)
{
	switch (reloc_op) {
	case RELOC_OP_ABS:
		return val;
	case RELOC_OP_PREL:
		return val - (u64)place;
	case RELOC_OP_PAGE:
		return (val & ~0xfff) - ((u64)place & ~0xfff);
	case RELOC_OP_NONE:
		return 0;
	}

	pr_err("do_reloc: unknown relocation operation %d\n", reloc_op);
	return 0;
}