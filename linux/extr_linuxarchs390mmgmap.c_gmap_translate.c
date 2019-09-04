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
struct gmap {TYPE_1__* mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 unsigned long __gmap_translate (struct gmap*,unsigned long) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

unsigned long gmap_translate(struct gmap *gmap, unsigned long gaddr)
{
	unsigned long rc;

	down_read(&gmap->mm->mmap_sem);
	rc = __gmap_translate(gmap, gaddr);
	up_read(&gmap->mm->mmap_sem);
	return rc;
}