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
struct dc_link_status {int dummy; } ;
struct dc_link {struct dc_link_status const link_status; } ;

/* Variables and functions */

const struct dc_link_status *dc_link_get_status(const struct dc_link *link)
{
	return &link->link_status;
}