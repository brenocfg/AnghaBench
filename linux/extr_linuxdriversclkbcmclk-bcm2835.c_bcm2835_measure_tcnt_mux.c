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
struct bcm2835_cprman {int /*<<< orphan*/  regs_lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int CM_BUSY ; 
 int CM_KILL ; 
 int /*<<< orphan*/  CM_OSCCOUNT ; 
 int CM_SRC_BITS ; 
 int CM_SRC_MASK ; 
 int /*<<< orphan*/  CM_TCNTCNT ; 
 int /*<<< orphan*/  CM_TCNTCTL ; 
 int CM_TCNT_SRC1_SHIFT ; 
 int /*<<< orphan*/  LOCK_TIMEOUT_NS ; 
 int cprman_read (struct bcm2835_cprman*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cprman_write (struct bcm2835_cprman*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long bcm2835_measure_tcnt_mux(struct bcm2835_cprman *cprman,
					      u32 tcnt_mux)
{
	u32 osccount = 19200; /* 1ms */
	u32 count;
	ktime_t timeout;

	spin_lock(&cprman->regs_lock);

	cprman_write(cprman, CM_TCNTCTL, CM_KILL);

	cprman_write(cprman, CM_TCNTCTL,
		     (tcnt_mux & CM_SRC_MASK) |
		     (tcnt_mux >> CM_SRC_BITS) << CM_TCNT_SRC1_SHIFT);

	cprman_write(cprman, CM_OSCCOUNT, osccount);

	/* do a kind delay at the start */
	mdelay(1);

	/* Finish off whatever is left of OSCCOUNT */
	timeout = ktime_add_ns(ktime_get(), LOCK_TIMEOUT_NS);
	while (cprman_read(cprman, CM_OSCCOUNT)) {
		if (ktime_after(ktime_get(), timeout)) {
			dev_err(cprman->dev, "timeout waiting for OSCCOUNT\n");
			count = 0;
			goto out;
		}
		cpu_relax();
	}

	/* Wait for BUSY to clear. */
	timeout = ktime_add_ns(ktime_get(), LOCK_TIMEOUT_NS);
	while (cprman_read(cprman, CM_TCNTCTL) & CM_BUSY) {
		if (ktime_after(ktime_get(), timeout)) {
			dev_err(cprman->dev, "timeout waiting for !BUSY\n");
			count = 0;
			goto out;
		}
		cpu_relax();
	}

	count = cprman_read(cprman, CM_TCNTCNT);

	cprman_write(cprman, CM_TCNTCTL, 0);

out:
	spin_unlock(&cprman->regs_lock);

	return count * 1000;
}