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
struct rvin_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNINTS_REG ; 
 int /*<<< orphan*/  rvin_read (struct rvin_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvin_write (struct rvin_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvin_ack_interrupt(struct rvin_dev *vin)
{
	rvin_write(vin, rvin_read(vin, VNINTS_REG), VNINTS_REG);
}