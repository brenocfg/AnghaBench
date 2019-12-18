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
struct scc_channel {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  EXINT 131 
#define  RXINT 130 
#define  SPINT 129 
#define  TXINT 128 
 int VECTOR_MASK ; 
 int /*<<< orphan*/  scc_exint (struct scc_channel*) ; 
 int /*<<< orphan*/  scc_rxint (struct scc_channel*) ; 
 int /*<<< orphan*/  scc_spint (struct scc_channel*) ; 
 int /*<<< orphan*/  scc_txint (struct scc_channel*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scc_isr_dispatch(struct scc_channel *scc, int vector)
{
	spin_lock(&scc->lock);
	switch (vector & VECTOR_MASK)
	{
		case TXINT: scc_txint(scc); break;
		case EXINT: scc_exint(scc); break;
		case RXINT: scc_rxint(scc); break;
		case SPINT: scc_spint(scc); break;
	}
	spin_unlock(&scc->lock);
}