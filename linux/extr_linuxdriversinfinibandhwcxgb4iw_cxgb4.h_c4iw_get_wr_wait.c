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
struct c4iw_wr_wait {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 scalar_t__ kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_wr_wait*,scalar_t__) ; 

__attribute__((used)) static inline void c4iw_get_wr_wait(struct c4iw_wr_wait *wr_waitp)
{
	pr_debug("wr_wait %p ref before get %u\n", wr_waitp,
		 kref_read(&wr_waitp->kref));
	WARN_ON(kref_read(&wr_waitp->kref) == 0);
	kref_get(&wr_waitp->kref);
}