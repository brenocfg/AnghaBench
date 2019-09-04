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
typedef  size_t u32 ;
struct frame {size_t tag; int /*<<< orphan*/  head; TYPE_1__* t; } ;
struct aoedev {int /*<<< orphan*/ * factive; } ;
struct TYPE_2__ {struct aoedev* d; } ;

/* Variables and functions */
 size_t NFACTIVE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fhash(struct frame *f)
{
	struct aoedev *d = f->t->d;
	u32 n;

	n = f->tag % NFACTIVE;
	list_add_tail(&f->head, &d->factive[n]);
}