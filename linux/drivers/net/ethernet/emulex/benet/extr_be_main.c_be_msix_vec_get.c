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
struct be_eq_obj {size_t msix_idx; } ;
struct be_adapter {TYPE_1__* msix_entries; } ;
struct TYPE_2__ {int vector; } ;

/* Variables and functions */

__attribute__((used)) static inline int be_msix_vec_get(struct be_adapter *adapter,
				  struct be_eq_obj *eqo)
{
	return adapter->msix_entries[eqo->msix_idx].vector;
}