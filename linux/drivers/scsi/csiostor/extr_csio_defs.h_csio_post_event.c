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
typedef  int /*<<< orphan*/  uint32_t ;
struct csio_sm {int /*<<< orphan*/  (* sm_state ) (void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
csio_post_event(void *smp, uint32_t evt)
{
	((struct csio_sm *)smp)->sm_state(smp, evt);
}