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
typedef  int /*<<< orphan*/  u64 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LODWORD (int /*<<< orphan*/ ) ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_itr_irq_msk_setlsw_set (struct aq_hw_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_atl_b0_hw_irq_enable(struct aq_hw_s *self, u64 mask)
{
	hw_atl_itr_irq_msk_setlsw_set(self, LODWORD(mask));
	return aq_hw_err_from_flags(self);
}