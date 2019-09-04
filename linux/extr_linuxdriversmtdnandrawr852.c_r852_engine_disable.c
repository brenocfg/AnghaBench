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
struct r852_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R852_CTL ; 
 int /*<<< orphan*/  R852_CTL_RESET ; 
 int /*<<< orphan*/  R852_HW ; 
 int /*<<< orphan*/  r852_write_reg (struct r852_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_write_reg_dword (struct r852_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r852_engine_disable(struct r852_device *dev)
{
	r852_write_reg_dword(dev, R852_HW, 0);
	r852_write_reg(dev, R852_CTL, R852_CTL_RESET);
}