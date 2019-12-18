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
struct mthca_eqe {int owner; } ;
struct mthca_eq {int /*<<< orphan*/  cons_index; } ;

/* Variables and functions */
 int MTHCA_EQ_ENTRY_OWNER_HW ; 
 struct mthca_eqe* get_eqe (struct mthca_eq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mthca_eqe *next_eqe_sw(struct mthca_eq *eq)
{
	struct mthca_eqe *eqe;
	eqe = get_eqe(eq, eq->cons_index);
	return (MTHCA_EQ_ENTRY_OWNER_HW & eqe->owner) ? NULL : eqe;
}