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
typedef  enum vmballoon_page_size_type { ____Placeholder_vmballoon_page_size_type } vmballoon_page_size_type ;

/* Variables and functions */
 unsigned int VMW_BALLOON_2M_ORDER ; 
 int VMW_BALLOON_2M_PAGE ; 

__attribute__((used)) static inline
unsigned int vmballoon_page_order(enum vmballoon_page_size_type page_size)
{
	return page_size == VMW_BALLOON_2M_PAGE ? VMW_BALLOON_2M_ORDER : 0;
}