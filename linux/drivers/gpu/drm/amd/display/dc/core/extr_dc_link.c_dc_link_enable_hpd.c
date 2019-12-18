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
struct dc_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_link_dp_enable_hpd (struct dc_link const*) ; 

void dc_link_enable_hpd(const struct dc_link *link)
{
	dc_link_dp_enable_hpd(link);
}