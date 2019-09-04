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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct c4iw_wr_wait* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_wr_wait*) ; 

struct c4iw_wr_wait *c4iw_alloc_wr_wait(gfp_t gfp)
{
	struct c4iw_wr_wait *wr_waitp;

	wr_waitp = kzalloc(sizeof(*wr_waitp), gfp);
	if (wr_waitp) {
		kref_init(&wr_waitp->kref);
		pr_debug("wr_wait %p\n", wr_waitp);
	}
	return wr_waitp;
}