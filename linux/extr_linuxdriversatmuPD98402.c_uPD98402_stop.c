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
struct atm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV (struct atm_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uPD98402_stop(struct atm_dev *dev)
{
	/* let SAR driver worry about stopping interrupts */
	kfree(PRIV(dev));
	return 0;
}