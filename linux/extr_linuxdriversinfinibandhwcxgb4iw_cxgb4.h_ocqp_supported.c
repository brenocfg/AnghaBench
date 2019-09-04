#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cxgb4_lld_info {TYPE_2__* vr; } ;
struct TYPE_3__ {scalar_t__ size; } ;
struct TYPE_4__ {TYPE_1__ ocq; } ;

/* Variables and functions */

__attribute__((used)) static inline int ocqp_supported(const struct cxgb4_lld_info *infop)
{
#if defined(__i386__) || defined(__x86_64__) || defined(CONFIG_PPC64)
	return infop->vr->ocq.size > 0;
#else
	return 0;
#endif
}