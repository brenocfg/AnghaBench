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
struct TYPE_2__ {int ithena; } ;
union cvmx_mixx_intena {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
struct octeon_mgmt {int /*<<< orphan*/  lock; scalar_t__ mix; } ;

/* Variables and functions */
 scalar_t__ MIX_INTENA ; 
 int /*<<< orphan*/  cvmx_read_csr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void octeon_mgmt_set_rx_irq(struct octeon_mgmt *p, int enable)
{
	union cvmx_mixx_intena mix_intena;
	unsigned long flags;

	spin_lock_irqsave(&p->lock, flags);
	mix_intena.u64 = cvmx_read_csr(p->mix + MIX_INTENA);
	mix_intena.s.ithena = enable ? 1 : 0;
	cvmx_write_csr(p->mix + MIX_INTENA, mix_intena.u64);
	spin_unlock_irqrestore(&p->lock, flags);
}