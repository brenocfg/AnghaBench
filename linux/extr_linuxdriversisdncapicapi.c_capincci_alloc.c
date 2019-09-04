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
typedef  int /*<<< orphan*/  u32 ;
struct capincci {int /*<<< orphan*/  list; struct capidev* cdev; int /*<<< orphan*/  ncci; } ;
struct capidev {int /*<<< orphan*/  nccis; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  capincci_alloc_minor (struct capidev*,struct capincci*) ; 
 struct capincci* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct capincci *capincci_alloc(struct capidev *cdev, u32 ncci)
{
	struct capincci *np;

	np = kzalloc(sizeof(*np), GFP_KERNEL);
	if (!np)
		return NULL;
	np->ncci = ncci;
	np->cdev = cdev;

	capincci_alloc_minor(cdev, np);

	list_add_tail(&np->list, &cdev->nccis);

	return np;
}