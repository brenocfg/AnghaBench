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
typedef  union event_ring_elem {int dummy; } event_ring_elem ;
struct bnx2x {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int bnx2x_iov_eq_sp_event(struct bnx2x *bp,
					union event_ring_elem *elem) {return 1; }