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
struct TYPE_2__ {unsigned int mbps; } ;
struct aq_nic_s {TYPE_1__ link_status; } ;

/* Variables and functions */

unsigned int aq_nic_get_link_speed(struct aq_nic_s *self)
{
	return self->link_status.mbps;
}