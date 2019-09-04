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
struct TYPE_2__ {int /*<<< orphan*/  cl; } ;
struct closure {int dummy; } ;
struct search {TYPE_1__ iop; struct closure cl; } ;
struct cached_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_lookup ; 
 int /*<<< orphan*/  cached_dev_read_done_bh ; 
 int /*<<< orphan*/  closure_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct closure*) ; 
 int /*<<< orphan*/  continue_at (struct closure*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cached_dev_read(struct cached_dev *dc, struct search *s)
{
	struct closure *cl = &s->cl;

	closure_call(&s->iop.cl, cache_lookup, NULL, cl);
	continue_at(cl, cached_dev_read_done_bh, NULL);
}