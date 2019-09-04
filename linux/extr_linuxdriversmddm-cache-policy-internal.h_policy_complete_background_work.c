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
struct policy_work {int dummy; } ;
struct dm_cache_policy {void (* complete_background_work ) (struct dm_cache_policy*,struct policy_work*,int) ;} ;

/* Variables and functions */
 void stub1 (struct dm_cache_policy*,struct policy_work*,int) ; 

__attribute__((used)) static inline void policy_complete_background_work(struct dm_cache_policy *p,
						   struct policy_work *work,
						   bool success)
{
	return p->complete_background_work(p, work, success);
}