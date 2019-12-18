#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* read_fw_domains ) (struct intel_uncore*,int /*<<< orphan*/ ) ;int (* write_fw_domains ) (struct intel_uncore*,int /*<<< orphan*/ ) ;} ;
struct intel_uncore {int fw_domains; TYPE_1__ funcs; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 unsigned int FW_REG_READ ; 
 unsigned int FW_REG_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  intel_uncore_has_forcewake (struct intel_uncore*) ; 
 int stub1 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int stub2 (struct intel_uncore*,int /*<<< orphan*/ ) ; 

enum forcewake_domains
intel_uncore_forcewake_for_reg(struct intel_uncore *uncore,
			       i915_reg_t reg, unsigned int op)
{
	enum forcewake_domains fw_domains = 0;

	WARN_ON(!op);

	if (!intel_uncore_has_forcewake(uncore))
		return 0;

	if (op & FW_REG_READ)
		fw_domains = uncore->funcs.read_fw_domains(uncore, reg);

	if (op & FW_REG_WRITE)
		fw_domains |= uncore->funcs.write_fw_domains(uncore, reg);

	WARN_ON(fw_domains & ~uncore->fw_domains);

	return fw_domains;
}