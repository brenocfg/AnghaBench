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
struct qlogicpti {scalar_t__ qregs; } ;

/* Variables and functions */
 scalar_t__ SBUS_CTRL ; 
 int /*<<< orphan*/  sbus_writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void qlogicpti_disable_irqs(struct qlogicpti *qpti)
{
	sbus_writew(0, qpti->qregs + SBUS_CTRL);
}