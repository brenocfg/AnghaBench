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
struct c4iw_wr_wait {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _c4iw_wake_up (struct c4iw_wr_wait*,int,int) ; 

__attribute__((used)) static inline void c4iw_wake_up_noref(struct c4iw_wr_wait *wr_waitp, int ret)
{
	_c4iw_wake_up(wr_waitp, ret, false);
}