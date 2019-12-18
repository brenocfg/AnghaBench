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
typedef  int /*<<< orphan*/  u32 ;
struct rproc {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* handle_rsc ) (struct rproc*,int /*<<< orphan*/ ,void*,int,int) ;} ;

/* Variables and functions */
 int RSC_IGNORED ; 
 int stub1 (struct rproc*,int /*<<< orphan*/ ,void*,int,int) ; 

__attribute__((used)) static inline
int rproc_handle_rsc(struct rproc *rproc, u32 rsc_type, void *rsc, int offset,
		     int avail)
{
	if (rproc->ops->handle_rsc)
		return rproc->ops->handle_rsc(rproc, rsc_type, rsc, offset,
					      avail);

	return RSC_IGNORED;
}