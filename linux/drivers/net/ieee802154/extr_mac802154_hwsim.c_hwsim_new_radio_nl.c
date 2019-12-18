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
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int hwsim_add_one (struct genl_info*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* mac802154hwsim_dev ; 

__attribute__((used)) static int hwsim_new_radio_nl(struct sk_buff *msg, struct genl_info *info)
{
	return hwsim_add_one(info, &mac802154hwsim_dev->dev, false);
}