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
struct cm_work {scalar_t__ mad_recv_wc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_free_recv_mad (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cm_work*) ; 

__attribute__((used)) static void cm_free_work(struct cm_work *work)
{
	if (work->mad_recv_wc)
		ib_free_recv_mad(work->mad_recv_wc);
	kfree(work);
}