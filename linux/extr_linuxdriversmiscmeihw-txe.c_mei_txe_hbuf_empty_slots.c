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
struct mei_txe_hw {int slots; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static int mei_txe_hbuf_empty_slots(struct mei_device *dev)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);

	return hw->slots;
}