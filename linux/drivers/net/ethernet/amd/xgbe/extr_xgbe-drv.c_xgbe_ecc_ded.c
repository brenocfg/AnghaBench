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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long ecc_ded_period ; 
 unsigned int ecc_ded_threshold ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  netdev_alert (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static bool xgbe_ecc_ded(struct xgbe_prv_data *pdata, unsigned long *period,
			 unsigned int *count, const char *area)
{
	if (time_before(jiffies, *period)) {
		(*count)++;
	} else {
		*period = jiffies + (ecc_ded_period * HZ);
		*count = 1;
	}

	if (*count > ecc_ded_threshold) {
		netdev_alert(pdata->netdev,
			     "%s ECC detected errors exceed threshold\n",
			     area);
		return true;
	}

	return false;
}