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
typedef  int u32 ;
struct arm_ccn {scalar_t__ base; int /*<<< orphan*/  dt; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ CCN_MN_ERRINT_STATUS ; 
 int /*<<< orphan*/  CCN_MN_ERRINT_STATUS__INTREQ__DESSERT ; 
 scalar_t__ CCN_MN_ERR_SIG_VAL_63_0 ; 
 int CCN_MN_ERR_SIG_VAL_63_0__DT ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  arm_ccn_error_handler (struct arm_ccn*,int*) ; 
 int /*<<< orphan*/  arm_ccn_pmu_overflow_handler (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t arm_ccn_irq_handler(int irq, void *dev_id)
{
	irqreturn_t res = IRQ_NONE;
	struct arm_ccn *ccn = dev_id;
	u32 err_sig_val[6];
	u32 err_or;
	int i;

	/* PMU overflow is a special case */
	err_or = err_sig_val[0] = readl(ccn->base + CCN_MN_ERR_SIG_VAL_63_0);
	if (err_or & CCN_MN_ERR_SIG_VAL_63_0__DT) {
		err_or &= ~CCN_MN_ERR_SIG_VAL_63_0__DT;
		res = arm_ccn_pmu_overflow_handler(&ccn->dt);
	}

	/* Have to read all err_sig_vals to clear them */
	for (i = 1; i < ARRAY_SIZE(err_sig_val); i++) {
		err_sig_val[i] = readl(ccn->base +
				CCN_MN_ERR_SIG_VAL_63_0 + i * 4);
		err_or |= err_sig_val[i];
	}
	if (err_or)
		res |= arm_ccn_error_handler(ccn, err_sig_val);

	if (res != IRQ_NONE)
		writel(CCN_MN_ERRINT_STATUS__INTREQ__DESSERT,
				ccn->base + CCN_MN_ERRINT_STATUS);

	return res;
}