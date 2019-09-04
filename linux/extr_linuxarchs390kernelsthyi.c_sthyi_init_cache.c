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
struct TYPE_2__ {scalar_t__ end; void* info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 TYPE_1__ sthyi_cache ; 

__attribute__((used)) static int sthyi_init_cache(void)
{
	if (sthyi_cache.info)
		return 0;
	sthyi_cache.info = (void *)get_zeroed_page(GFP_KERNEL);
	if (!sthyi_cache.info)
		return -ENOMEM;
	sthyi_cache.end = jiffies - 1; /* expired */
	return 0;
}