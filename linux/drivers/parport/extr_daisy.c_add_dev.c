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
struct parport {int dummy; } ;
struct daisydev {int daisy; int devnum; struct daisydev* next; struct parport* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct daisydev* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct daisydev* topology ; 
 int /*<<< orphan*/  topology_lock ; 

__attribute__((used)) static void add_dev(int devnum, struct parport *port, int daisy)
{
	struct daisydev *newdev, **p;
	newdev = kmalloc(sizeof(struct daisydev), GFP_KERNEL);
	if (newdev) {
		newdev->port = port;
		newdev->daisy = daisy;
		newdev->devnum = devnum;
		spin_lock(&topology_lock);
		for (p = &topology; *p && (*p)->devnum<devnum; p = &(*p)->next)
			;
		newdev->next = *p;
		*p = newdev;
		spin_unlock(&topology_lock);
	}
}