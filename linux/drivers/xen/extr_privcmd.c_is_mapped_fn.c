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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_mapped_fn(pte_t *pte, unsigned long addr, void *data)
{
	return pte_none(*pte) ? 0 : -EBUSY;
}