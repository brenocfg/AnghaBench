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
typedef  int /*<<< orphan*/  real_pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  __rpte_to_hidx (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  hpte_soft_invalid (int /*<<< orphan*/ ) ; 

bool __rpte_sub_valid(real_pte_t rpte, unsigned long index)
{
	return !(hpte_soft_invalid(__rpte_to_hidx(rpte, index)));
}