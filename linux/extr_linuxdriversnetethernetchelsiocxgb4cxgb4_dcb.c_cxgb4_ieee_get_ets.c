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
struct ieee_ets {int dummy; } ;

/* Variables and functions */
 int cxgb4_ieee_read_ets (struct net_device*,struct ieee_ets*,int) ; 

__attribute__((used)) static int cxgb4_ieee_get_ets(struct net_device *dev, struct ieee_ets *ets)
{
	return cxgb4_ieee_read_ets(dev, ets, 1);
}