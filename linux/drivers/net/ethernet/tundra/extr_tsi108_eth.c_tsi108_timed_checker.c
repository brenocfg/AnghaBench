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
struct tsi108_prv_data {int /*<<< orphan*/  timer; struct net_device* dev; } ;
struct timer_list {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHECK_PHY_INTERVAL ; 
 struct tsi108_prv_data* data ; 
 struct tsi108_prv_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  tsi108_check_phy (struct net_device*) ; 
 int /*<<< orphan*/  tsi108_check_rxring (struct net_device*) ; 

__attribute__((used)) static void tsi108_timed_checker(struct timer_list *t)
{
	struct tsi108_prv_data *data = from_timer(data, t, timer);
	struct net_device *dev = data->dev;

	tsi108_check_phy(dev);
	tsi108_check_rxring(dev);
	mod_timer(&data->timer, jiffies + CHECK_PHY_INTERVAL);
}