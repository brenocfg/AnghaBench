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
struct zs_scc {int /*<<< orphan*/  zlock; } ;
struct zs_port {struct zs_scc* scc; } ;

/* Variables and functions */
 int ALL_SNT ; 
 int /*<<< orphan*/  R1 ; 
 int read_zsreg (struct zs_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  zs_spin_lock_cond_irq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zs_spin_unlock_cond_irq (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int zs_line_drain(struct zs_port *zport, int irq)
{
	struct zs_scc *scc = zport->scc;
	int loops = 10000;

	while (!(read_zsreg(zport, R1) & ALL_SNT) && --loops) {
		zs_spin_unlock_cond_irq(&scc->zlock, irq);
		udelay(2);
		zs_spin_lock_cond_irq(&scc->zlock, irq);
	}
	return loops;
}