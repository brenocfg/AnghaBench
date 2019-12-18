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
typedef  int /*<<< orphan*/  u32 ;
struct csc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSC_BYPASS ; 

void csc_set_coeff_bypass(struct csc_data *csc, u32 *csc_reg5)
{
	*csc_reg5 |= CSC_BYPASS;
}