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
struct TYPE_2__ {scalar_t__ (* check_pending ) (TYPE_1__*) ;} ;
struct bnx2x_mcast_obj {scalar_t__ (* check_sched ) (struct bnx2x_mcast_obj*) ;TYPE_1__ raw; } ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_1__*) ; 
 scalar_t__ stub2 (struct bnx2x_mcast_obj*) ; 

__attribute__((used)) static bool bnx2x_mcast_check_pending(struct bnx2x_mcast_obj *o)
{
	return o->raw.check_pending(&o->raw) || o->check_sched(o);
}