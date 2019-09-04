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
typedef  int /*<<< orphan*/  u32 ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mei_txe_readiness_get (struct mei_device*) ; 
 int mei_txe_readiness_is_sec_rdy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mei_txe_hw_is_ready(struct mei_device *dev)
{
	u32 readiness =  mei_txe_readiness_get(dev);

	return mei_txe_readiness_is_sec_rdy(readiness);
}