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
struct TYPE_2__ {int /*<<< orphan*/  io_lock; scalar_t__ io_addr; } ;

/* Variables and functions */
 int PCWD_REVISION_A ; 
 int PCWD_REVISION_C ; 
 int inb (scalar_t__) ; 
 TYPE_1__ pcwd_private ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_revision(void)
{
	int r = PCWD_REVISION_C;

	spin_lock(&pcwd_private.io_lock);
	/* REV A cards use only 2 io ports; test
	 * presumes a floating bus reads as 0xff. */
	if ((inb(pcwd_private.io_addr + 2) == 0xFF) ||
	    (inb(pcwd_private.io_addr + 3) == 0xFF))
		r = PCWD_REVISION_A;
	spin_unlock(&pcwd_private.io_lock);

	return r;
}