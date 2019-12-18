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
struct vfio_pci_reflck {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflck_lock ; 
 int /*<<< orphan*/  vfio_pci_reflck_release ; 

__attribute__((used)) static void vfio_pci_reflck_put(struct vfio_pci_reflck *reflck)
{
	kref_put_mutex(&reflck->kref, vfio_pci_reflck_release, &reflck_lock);
}