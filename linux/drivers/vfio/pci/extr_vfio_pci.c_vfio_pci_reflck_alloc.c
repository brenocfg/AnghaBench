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
struct vfio_pci_reflck {int /*<<< orphan*/  lock; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct vfio_pci_reflck* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct vfio_pci_reflck* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vfio_pci_reflck *vfio_pci_reflck_alloc(void)
{
	struct vfio_pci_reflck *reflck;

	reflck = kzalloc(sizeof(*reflck), GFP_KERNEL);
	if (!reflck)
		return ERR_PTR(-ENOMEM);

	kref_init(&reflck->kref);
	mutex_init(&reflck->lock);

	return reflck;
}