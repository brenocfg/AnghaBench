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
struct i3c_ibi_slot {int /*<<< orphan*/  work; struct i3c_dev_desc* dev; } ;
struct i3c_dev_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_master_handle_ibi ; 

__attribute__((used)) static void i3c_master_init_ibi_slot(struct i3c_dev_desc *dev,
				     struct i3c_ibi_slot *slot)
{
	slot->dev = dev;
	INIT_WORK(&slot->work, i3c_master_handle_ibi);
}