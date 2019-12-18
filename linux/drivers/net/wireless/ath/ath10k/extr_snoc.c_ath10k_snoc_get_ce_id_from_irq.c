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
struct ath10k_snoc {TYPE_1__* ce_irqs; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {int irq_line; } ;

/* Variables and functions */
 int CE_COUNT_MAX ; 
 int EINVAL ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 

__attribute__((used)) static int ath10k_snoc_get_ce_id_from_irq(struct ath10k *ar, int irq)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	int i;

	for (i = 0; i < CE_COUNT_MAX; i++) {
		if (ar_snoc->ce_irqs[i].irq_line == irq)
			return i;
	}
	ath10k_err(ar, "No matching CE id for irq %d\n", irq);

	return -EINVAL;
}