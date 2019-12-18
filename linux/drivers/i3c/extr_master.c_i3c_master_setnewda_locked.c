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
struct i3c_master_controller {int dummy; } ;

/* Variables and functions */
 int i3c_master_setda_locked (struct i3c_master_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i3c_master_setnewda_locked(struct i3c_master_controller *master,
				      u8 oldaddr, u8 newaddr)
{
	return i3c_master_setda_locked(master, oldaddr, newaddr, false);
}