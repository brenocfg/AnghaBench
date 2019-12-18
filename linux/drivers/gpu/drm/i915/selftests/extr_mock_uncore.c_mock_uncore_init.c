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
struct intel_uncore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_RAW_READ_MMIO_VFUNCS (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSIGN_RAW_WRITE_MMIO_VFUNCS (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nop ; 

void mock_uncore_init(struct intel_uncore *uncore)
{
	ASSIGN_RAW_WRITE_MMIO_VFUNCS(uncore, nop);
	ASSIGN_RAW_READ_MMIO_VFUNCS(uncore, nop);
}