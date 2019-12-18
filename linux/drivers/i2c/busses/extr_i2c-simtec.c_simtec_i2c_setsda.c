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
struct simtec_i2c_data {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int CMD_SET_SDA ; 
 int STATE_SDA ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void simtec_i2c_setsda(void *pw, int state)
{
	struct simtec_i2c_data *pd = pw;
	writeb(CMD_SET_SDA | (state ? STATE_SDA : 0), pd->reg);
}