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
struct ath10k_snoc {int /*<<< orphan*/  pipe_info; } ;
struct ath10k {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int ath10k_snoc_get_ce_id_from_irq (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_snoc_irq_disable (struct ath10k*) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ath10k_snoc_per_engine_handler(int irq, void *arg)
{
	struct ath10k *ar = arg;
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	int ce_id = ath10k_snoc_get_ce_id_from_irq(ar, irq);

	if (ce_id < 0 || ce_id >= ARRAY_SIZE(ar_snoc->pipe_info)) {
		ath10k_warn(ar, "unexpected/invalid irq %d ce_id %d\n", irq,
			    ce_id);
		return IRQ_HANDLED;
	}

	ath10k_snoc_irq_disable(ar);
	napi_schedule(&ar->napi);

	return IRQ_HANDLED;
}