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
typedef  int /*<<< orphan*/  u16 ;
struct i40iw_sc_pd {int size; int abi_ver; struct i40iw_sc_dev* dev; int /*<<< orphan*/  pd_id; } ;
struct i40iw_sc_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void i40iw_sc_pd_init(struct i40iw_sc_dev *dev,
			     struct i40iw_sc_pd *pd,
			     u16 pd_id,
			     int abi_ver)
{
	pd->size = sizeof(*pd);
	pd->pd_id = pd_id;
	pd->abi_ver = abi_ver;
	pd->dev = dev;
}