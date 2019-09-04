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
typedef  int /*<<< orphan*/  u32 ;
struct cppi41_channel {int /*<<< orphan*/  q_comp_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_TYPE_USB ; 

__attribute__((used)) static u32 get_host_pd2(struct cppi41_channel *c)
{
	u32 reg;

	reg = DESC_TYPE_USB;
	reg |= c->q_comp_num;

	return reg;
}