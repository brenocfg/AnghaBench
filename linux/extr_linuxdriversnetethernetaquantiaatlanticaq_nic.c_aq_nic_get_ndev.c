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
struct net_device {int dummy; } ;
struct aq_nic_s {struct net_device* ndev; } ;

/* Variables and functions */

struct net_device *aq_nic_get_ndev(struct aq_nic_s *self)
{
	return self->ndev;
}