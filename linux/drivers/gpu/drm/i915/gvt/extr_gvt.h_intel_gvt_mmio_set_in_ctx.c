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
struct TYPE_2__ {int /*<<< orphan*/ * mmio_attribute; } ;
struct intel_gvt {TYPE_1__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_IN_CTX ; 

__attribute__((used)) static inline void intel_gvt_mmio_set_in_ctx(
			struct intel_gvt *gvt, unsigned int offset)
{
	gvt->mmio.mmio_attribute[offset >> 2] |= F_IN_CTX;
}