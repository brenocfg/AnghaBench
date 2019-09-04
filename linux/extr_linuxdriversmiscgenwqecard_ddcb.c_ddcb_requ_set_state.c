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
struct ddcb_requ {int req_state; } ;
typedef  enum genwqe_requ_state { ____Placeholder_genwqe_requ_state } genwqe_requ_state ;

/* Variables and functions */

__attribute__((used)) static inline void ddcb_requ_set_state(struct ddcb_requ *req,
				       enum genwqe_requ_state new_state)
{
	req->req_state = new_state;
}