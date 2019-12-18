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
struct ipu_ic_csc {int dummy; } ;

/* Variables and functions */
 int calc_csc_coeffs (struct ipu_ic_csc*) ; 

int __ipu_ic_calc_csc(struct ipu_ic_csc *csc)
{
	return calc_csc_coeffs(csc);
}