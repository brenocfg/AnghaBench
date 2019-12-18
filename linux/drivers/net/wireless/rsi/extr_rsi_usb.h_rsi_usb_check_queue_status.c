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
typedef  int /*<<< orphan*/  u8 ;
struct rsi_hw {int dummy; } ;

/* Variables and functions */
 int QUEUE_NOT_FULL ; 

__attribute__((used)) static inline int rsi_usb_check_queue_status(struct rsi_hw *adapter, u8 q_num)
{
	/* In USB, there isn't any need to check the queue status */
	return QUEUE_NOT_FULL;
}