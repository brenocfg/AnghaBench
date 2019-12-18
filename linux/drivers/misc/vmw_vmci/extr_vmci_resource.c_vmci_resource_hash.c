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
struct vmci_handle {int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_RESOURCE_HASH_BITS ; 
 unsigned int hash_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int vmci_resource_hash(struct vmci_handle handle)
{
	return hash_32(handle.resource, VMCI_RESOURCE_HASH_BITS);
}