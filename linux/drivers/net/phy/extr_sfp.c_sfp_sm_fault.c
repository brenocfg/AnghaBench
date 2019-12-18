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
struct sfp {int /*<<< orphan*/  dev; scalar_t__ sm_retries; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFP_S_TX_DISABLE ; 
 int /*<<< orphan*/  SFP_S_TX_FAULT ; 
 int /*<<< orphan*/  T_FAULT_RECOVER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sfp_sm_next (struct sfp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfp_sm_fault(struct sfp *sfp, bool warn)
{
	if (sfp->sm_retries && !--sfp->sm_retries) {
		dev_err(sfp->dev,
			"module persistently indicates fault, disabling\n");
		sfp_sm_next(sfp, SFP_S_TX_DISABLE, 0);
	} else {
		if (warn)
			dev_err(sfp->dev, "module transmit fault indicated\n");

		sfp_sm_next(sfp, SFP_S_TX_FAULT, T_FAULT_RECOVER);
	}
}