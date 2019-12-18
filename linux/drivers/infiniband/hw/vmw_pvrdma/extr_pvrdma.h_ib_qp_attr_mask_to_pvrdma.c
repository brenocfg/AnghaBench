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

/* Variables and functions */
 int PVRDMA_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVRDMA_QP_ATTR_MASK_MAX ; 

__attribute__((used)) static inline int ib_qp_attr_mask_to_pvrdma(int attr_mask)
{
	return attr_mask & PVRDMA_MASK(PVRDMA_QP_ATTR_MASK_MAX);
}