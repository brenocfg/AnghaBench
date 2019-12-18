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
struct pasid_entry {int dummy; } ;
struct pasid_dir_entry {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int PDE_PFN_MASK ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasid_pde_is_present (struct pasid_dir_entry*) ; 
 struct pasid_entry* phys_to_virt (int) ; 

__attribute__((used)) static inline struct pasid_entry *
get_pasid_table_from_pde(struct pasid_dir_entry *pde)
{
	if (!pasid_pde_is_present(pde))
		return NULL;

	return phys_to_virt(READ_ONCE(pde->val) & PDE_PFN_MASK);
}