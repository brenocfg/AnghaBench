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
struct rvin_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNINTS_REG ; 
 int /*<<< orphan*/  rvin_read (struct rvin_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 rvin_get_interrupt_status(struct rvin_dev *vin)
{
	return rvin_read(vin, VNINTS_REG);
}