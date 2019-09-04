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
struct drxd_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRX_I2C_BROADCAST ; 
 int /*<<< orphan*/  HI_COMM_EXEC__A ; 
 int /*<<< orphan*/  SC_COMM_EXEC_CTL_STOP ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int StopAllProcessors(struct drxd_state *state)
{
	return Write16(state, HI_COMM_EXEC__A,
		       SC_COMM_EXEC_CTL_STOP, DRX_I2C_BROADCAST);
}