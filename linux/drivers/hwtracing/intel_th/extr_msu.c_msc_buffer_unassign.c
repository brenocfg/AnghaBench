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
struct msc {TYPE_1__* mbuf; int /*<<< orphan*/ * mbuf_priv; int /*<<< orphan*/  buf_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unassign ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msu_buffer_put (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msc_buffer_unassign(struct msc *msc)
{
	lockdep_assert_held(&msc->buf_mutex);

	if (!msc->mbuf)
		return;

	msc->mbuf->unassign(msc->mbuf_priv);
	msu_buffer_put(msc->mbuf);
	msc->mbuf_priv = NULL;
	msc->mbuf = NULL;
}