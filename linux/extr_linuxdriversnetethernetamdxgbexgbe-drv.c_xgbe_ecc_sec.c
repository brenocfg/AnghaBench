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
struct xgbe_prv_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ ,char*,char const*) ; 
 unsigned int ecc_sec_info_threshold ; 
 unsigned long ecc_sec_period ; 
 unsigned int ecc_sec_warn_threshold ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static bool xgbe_ecc_sec(struct xgbe_prv_data *pdata, unsigned long *period,
			 unsigned int *count, const char *area)
{
	if (time_before(jiffies, *period)) {
		(*count)++;
	} else {
		*period = jiffies + (ecc_sec_period * HZ);
		*count = 1;
	}

	if (*count > ecc_sec_info_threshold)
		dev_warn_once(pdata->dev,
			      "%s ECC corrected errors exceed informational threshold\n",
			      area);

	if (*count > ecc_sec_warn_threshold) {
		dev_warn_once(pdata->dev,
			      "%s ECC corrected errors exceed warning threshold\n",
			      area);
		return true;
	}

	return false;
}