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
 int /*<<< orphan*/  ATM_PHY_SIG_FOUND ; 
 int /*<<< orphan*/  ATM_PHY_SIG_LOST ; 
 int GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSOP_SIS ; 
 int SUNI_RSOP_SIS_LOSV ; 
 int /*<<< orphan*/  atm_dev_signal_change (struct atm_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poll_los(struct atm_dev *dev)
{
	atm_dev_signal_change(dev,
		GET(RSOP_SIS) & SUNI_RSOP_SIS_LOSV ?
		ATM_PHY_SIG_LOST : ATM_PHY_SIG_FOUND);
}