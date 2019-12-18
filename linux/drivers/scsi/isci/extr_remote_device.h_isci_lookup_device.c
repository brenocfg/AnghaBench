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
struct isci_remote_device {int /*<<< orphan*/  kref; int /*<<< orphan*/  flags; } ;
struct domain_device {struct isci_remote_device* lldd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDEV_GONE ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct isci_remote_device *isci_lookup_device(struct domain_device *dev)
{
	struct isci_remote_device *idev = dev->lldd_dev;

	if (idev && !test_bit(IDEV_GONE, &idev->flags)) {
		kref_get(&idev->kref);
		return idev;
	}

	return NULL;
}