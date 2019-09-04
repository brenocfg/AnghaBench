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
struct lgdt3306a_state {int dummy; } ;

/* Variables and functions */
 int lgdt3306a_read_reg (struct lgdt3306a_state*,int,int*) ; 

__attribute__((used)) static u8 lgdt3306a_get_packet_error(struct lgdt3306a_state *state)
{
	u8 val;
	int ret;

	ret = lgdt3306a_read_reg(state, 0x00fa, &val);
	if (ret)
		return ret;

	return val;
}