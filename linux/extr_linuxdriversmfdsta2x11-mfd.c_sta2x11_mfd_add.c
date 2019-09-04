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
struct sta2x11_mfd {int /*<<< orphan*/  list; struct sta2x11_instance* instance; int /*<<< orphan*/ * lock; } ;
struct sta2x11_instance {int dummy; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct sta2x11_mfd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct sta2x11_instance* sta2x11_get_instance (struct pci_dev*) ; 
 struct sta2x11_mfd* sta2x11_mfd_find (struct pci_dev*) ; 
 int /*<<< orphan*/  sta2x11_mfd_list ; 

__attribute__((used)) static int sta2x11_mfd_add(struct pci_dev *pdev, gfp_t flags)
{
	int i;
	struct sta2x11_mfd *mfd = sta2x11_mfd_find(pdev);
	struct sta2x11_instance *instance;

	if (mfd)
		return -EBUSY;
	instance = sta2x11_get_instance(pdev);
	if (!instance)
		return -EINVAL;
	mfd = kzalloc(sizeof(*mfd), flags);
	if (!mfd)
		return -ENOMEM;
	INIT_LIST_HEAD(&mfd->list);
	for (i = 0; i < ARRAY_SIZE(mfd->lock); i++)
		spin_lock_init(&mfd->lock[i]);
	mfd->instance = instance;
	list_add(&mfd->list, &sta2x11_mfd_list);
	return 0;
}