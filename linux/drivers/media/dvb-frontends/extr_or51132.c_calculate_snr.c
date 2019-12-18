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
typedef  int u32 ;

/* Variables and functions */
 int intlog10 (int) ; 

__attribute__((used)) static u32 calculate_snr(u32 mse, u32 c)
{
	if (mse == 0) /* No signal */
		return 0;

	mse = 2*intlog10(mse);
	if (mse > c) {
		/* Negative SNR, which is possible, but realisticly the
		demod will lose lock before the signal gets this bad.  The
		API only allows for unsigned values, so just return 0 */
		return 0;
	}
	return 10*(c - mse);
}