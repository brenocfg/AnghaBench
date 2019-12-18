#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct si2165_state {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const,scalar_t__) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/  const,unsigned int*) ; 

__attribute__((used)) static int si2165_readreg8(struct si2165_state *state,
			   const u16 reg, u8 *val)
{
	unsigned int val_tmp;
	int ret = regmap_read(state->regmap, reg, &val_tmp);
	*val = (u8)val_tmp;
	dev_dbg(&state->client->dev, "reg read: R(0x%04x)=0x%02x\n", reg, *val);
	return ret;
}