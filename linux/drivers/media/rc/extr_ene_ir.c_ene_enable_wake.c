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
struct ene_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_FW1 ; 
 int /*<<< orphan*/  ENE_FW1_WAKE ; 
 int /*<<< orphan*/  dbg (char*,char*) ; 
 int /*<<< orphan*/  ene_set_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ene_enable_wake(struct ene_device *dev, bool enable)
{
	dbg("wake on IR %s", enable ? "enabled" : "disabled");
	ene_set_clear_reg_mask(dev, ENE_FW1, ENE_FW1_WAKE, enable);
}