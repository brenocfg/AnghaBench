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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 unsigned int CMUCTRL5 ; 
 unsigned int EPB_IB_QUAD0_CS_SHF ; 
 int /*<<< orphan*/  IB_7220_SERDES ; 
 int qib_sd7220_reg_mod (struct qib_devdata*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int qib_sd_trimself(struct qib_devdata *dd, int val)
{
	int loc = CMUCTRL5 | (1U << EPB_IB_QUAD0_CS_SHF);

	return qib_sd7220_reg_mod(dd, IB_7220_SERDES, loc, val, 0xFF);
}