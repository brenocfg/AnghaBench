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
struct most_dci_obj {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct most_dci_obj*) ; 
 struct most_dci_obj* to_dci_obj (struct device*) ; 

__attribute__((used)) static void release_dci(struct device *dev)
{
	struct most_dci_obj *dci = to_dci_obj(dev);

	kfree(dci);
}