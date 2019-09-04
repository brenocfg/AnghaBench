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
typedef  int u8 ;
struct dc_i2c {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ II_COMMAND ; 
 int II_COMMAND_GO ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void dc_i2c_cmd(struct dc_i2c *i2c, u8 cmd)
{
	writeb_relaxed(cmd | II_COMMAND_GO, i2c->regs + II_COMMAND);
}