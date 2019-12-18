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
struct roce_hem_item {int start; int end; } ;

/* Variables and functions */

__attribute__((used)) static inline bool hem_list_page_is_in_range(struct roce_hem_item *hem,
					     int offset)
{
	return (hem->start <= offset && offset <= hem->end);
}