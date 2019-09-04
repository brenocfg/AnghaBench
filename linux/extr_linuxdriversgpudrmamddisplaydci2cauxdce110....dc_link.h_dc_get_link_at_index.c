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
typedef  size_t uint32_t ;
struct dc_link {int dummy; } ;
struct dc {struct dc_link** links; } ;

/* Variables and functions */

__attribute__((used)) static inline struct dc_link *dc_get_link_at_index(struct dc *dc, uint32_t link_index)
{
	return dc->links[link_index];
}