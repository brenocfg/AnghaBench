#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mthca_eqe {int dummy; } ;
struct mthca_eq {int nent; TYPE_1__* page_list; } ;
struct TYPE_2__ {struct mthca_eqe* buf; } ;

/* Variables and functions */
 int MTHCA_EQ_ENTRY_SIZE ; 
 unsigned long PAGE_SIZE ; 

__attribute__((used)) static inline struct mthca_eqe *get_eqe(struct mthca_eq *eq, u32 entry)
{
	unsigned long off = (entry & (eq->nent - 1)) * MTHCA_EQ_ENTRY_SIZE;
	return eq->page_list[off / PAGE_SIZE].buf + off % PAGE_SIZE;
}