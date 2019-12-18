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
struct coeff {int dummy; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int AR9300_MAX_CHAINS ; 
 int MAXIQCAL ; 
 int /*<<< orphan*/  __ar955x_tx_iq_cal_sort (struct ath_hw*,struct coeff*,int,int) ; 

__attribute__((used)) static bool ar955x_tx_iq_cal_median(struct ath_hw *ah,
				    struct coeff *coeff,
				    int iqcal_idx,
				    int nmeasurement)
{
	int i;

	if ((iqcal_idx + 1) != MAXIQCAL)
		return false;

	for (i = 0; i < AR9300_MAX_CHAINS; i++) {
		__ar955x_tx_iq_cal_sort(ah, coeff, i, nmeasurement);
	}

	return true;
}