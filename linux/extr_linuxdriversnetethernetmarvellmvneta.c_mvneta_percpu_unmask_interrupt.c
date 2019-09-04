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
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_INTR_NEW_MASK ; 
 int MVNETA_MISCINTR_INTR_MASK ; 
 int MVNETA_RX_INTR_MASK_ALL ; 
 int MVNETA_TX_INTR_MASK_ALL ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvneta_percpu_unmask_interrupt(void *arg)
{
	struct mvneta_port *pp = arg;

	/* All the queue are unmasked, but actually only the ones
	 * mapped to this CPU will be unmasked
	 */
	mvreg_write(pp, MVNETA_INTR_NEW_MASK,
		    MVNETA_RX_INTR_MASK_ALL |
		    MVNETA_TX_INTR_MASK_ALL |
		    MVNETA_MISCINTR_INTR_MASK);
}