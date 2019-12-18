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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int __IFLA_CAIF_HSI_MAX ; 
 int __IFLA_CAIF_HSI_UNSPEC ; 
 TYPE_1__* caif_hsi_policy ; 
 scalar_t__ nla_total_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t caif_hsi_get_size(const struct net_device *dev)
{
	int i;
	size_t s = 0;
	for (i = __IFLA_CAIF_HSI_UNSPEC + 1; i < __IFLA_CAIF_HSI_MAX; i++)
		s += nla_total_size(caif_hsi_policy[i].len);
	return s;
}