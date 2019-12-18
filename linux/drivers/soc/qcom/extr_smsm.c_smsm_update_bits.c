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
typedef  size_t u32 ;
struct smsm_host {int /*<<< orphan*/  ipc_bit; int /*<<< orphan*/  ipc_offset; scalar_t__ ipc_regmap; } ;
struct qcom_smsm {size_t num_hosts; scalar_t__ subscription; struct smsm_host* hosts; int /*<<< orphan*/  lock; scalar_t__ local_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 size_t readl (scalar_t__) ; 
 int /*<<< orphan*/  regmap_write (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (size_t,scalar_t__) ; 

__attribute__((used)) static int smsm_update_bits(void *data, u32 mask, u32 value)
{
	struct qcom_smsm *smsm = data;
	struct smsm_host *hostp;
	unsigned long flags;
	u32 changes;
	u32 host;
	u32 orig;
	u32 val;

	spin_lock_irqsave(&smsm->lock, flags);

	/* Update the entry */
	val = orig = readl(smsm->local_state);
	val &= ~mask;
	val |= value;

	/* Don't signal if we didn't change the value */
	changes = val ^ orig;
	if (!changes) {
		spin_unlock_irqrestore(&smsm->lock, flags);
		goto done;
	}

	/* Write out the new value */
	writel(val, smsm->local_state);
	spin_unlock_irqrestore(&smsm->lock, flags);

	/* Make sure the value update is ordered before any kicks */
	wmb();

	/* Iterate over all hosts to check whom wants a kick */
	for (host = 0; host < smsm->num_hosts; host++) {
		hostp = &smsm->hosts[host];

		val = readl(smsm->subscription + host);
		if (val & changes && hostp->ipc_regmap) {
			regmap_write(hostp->ipc_regmap,
				     hostp->ipc_offset,
				     BIT(hostp->ipc_bit));
		}
	}

done:
	return 0;
}