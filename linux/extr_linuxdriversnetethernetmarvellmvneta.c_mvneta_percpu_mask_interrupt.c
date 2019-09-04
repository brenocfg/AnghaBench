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
 int /*<<< orphan*/  MVNETA_INTR_MISC_MASK ; 
 int /*<<< orphan*/  MVNETA_INTR_NEW_MASK ; 
 int /*<<< orphan*/  MVNETA_INTR_OLD_MASK ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_percpu_mask_interrupt(void *arg)
{
	struct mvneta_port *pp = arg;

	/* All the queue are masked, but actually only the ones
	 * mapped to this CPU will be masked
	 */
	mvreg_write(pp, MVNETA_INTR_NEW_MASK, 0);
	mvreg_write(pp, MVNETA_INTR_OLD_MASK, 0);
	mvreg_write(pp, MVNETA_INTR_MISC_MASK, 0);
}