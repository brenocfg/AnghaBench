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
struct lgs8gl5_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lgs8gl5_read_reg (struct lgs8gl5_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lgs8gl5_write_reg (struct lgs8gl5_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lgs8gl5_update_reg(struct lgs8gl5_state *state, u8 reg, u8 data)
{
	lgs8gl5_read_reg(state, reg);
	lgs8gl5_write_reg(state, reg, data);
	return 0;
}