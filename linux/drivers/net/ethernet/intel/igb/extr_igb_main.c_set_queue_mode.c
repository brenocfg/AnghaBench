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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  enum queue_mode { ____Placeholder_queue_mode } queue_mode ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_I210_TQAVCC (int) ; 
 int /*<<< orphan*/  E1000_TQAVCC_QUEUEMODE ; 
 int QUEUE_MODE_STREAM_RESERVATION ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ e1000_i210 ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_queue_mode(struct e1000_hw *hw, int queue, enum queue_mode mode)
{
	u32 val;

	WARN_ON(hw->mac.type != e1000_i210);
	WARN_ON(queue < 0 || queue > 1);

	val = rd32(E1000_I210_TQAVCC(queue));

	if (mode == QUEUE_MODE_STREAM_RESERVATION)
		val |= E1000_TQAVCC_QUEUEMODE;
	else
		val &= ~E1000_TQAVCC_QUEUEMODE;

	wr32(E1000_I210_TQAVCC(queue), val);
}