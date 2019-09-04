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
typedef  void* uint64_t ;
struct debug_reg {int /*<<< orphan*/  dbcr0; void* iac2; void* iac1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBCR0_IAC1 ; 
 int /*<<< orphan*/  DBCR0_IAC2 ; 
 int /*<<< orphan*/  DBCR0_IDM ; 
 int EINVAL ; 

__attribute__((used)) static int kvmppc_booke_add_breakpoint(struct debug_reg *dbg_reg,
				       uint64_t addr, int index)
{
	switch (index) {
	case 0:
		dbg_reg->dbcr0 |= DBCR0_IAC1;
		dbg_reg->iac1 = addr;
		break;
	case 1:
		dbg_reg->dbcr0 |= DBCR0_IAC2;
		dbg_reg->iac2 = addr;
		break;
#if CONFIG_PPC_ADV_DEBUG_IACS > 2
	case 2:
		dbg_reg->dbcr0 |= DBCR0_IAC3;
		dbg_reg->iac3 = addr;
		break;
	case 3:
		dbg_reg->dbcr0 |= DBCR0_IAC4;
		dbg_reg->iac4 = addr;
		break;
#endif
	default:
		return -EINVAL;
	}

	dbg_reg->dbcr0 |= DBCR0_IDM;
	return 0;
}