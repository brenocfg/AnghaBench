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
struct f34_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F34_ENABLE_FLASH_PROG ; 
 int /*<<< orphan*/  F34_ENABLE_WAIT_MS ; 
 int rmi_f34_command (struct f34_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rmi_f34_enable_flash(struct f34_data *f34)
{
	return rmi_f34_command(f34, F34_ENABLE_FLASH_PROG,
			       F34_ENABLE_WAIT_MS, true);
}