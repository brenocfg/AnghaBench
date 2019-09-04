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
struct mthca_cqe {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTHCA_CQ_ENTRY_OWNER_HW ; 

__attribute__((used)) static inline void set_cqe_hw(struct mthca_cqe *cqe)
{
	cqe->owner = MTHCA_CQ_ENTRY_OWNER_HW;
}