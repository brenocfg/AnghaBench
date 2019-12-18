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
typedef  union qm_mr_entry {int dummy; } qm_mr_entry ;

/* Variables and functions */
 uintptr_t MR_CARRY ; 

__attribute__((used)) static union qm_mr_entry *mr_carryclear(union qm_mr_entry *p)
{
	uintptr_t addr = (uintptr_t)p;

	addr &= ~MR_CARRY;

	return (union qm_mr_entry *)addr;
}