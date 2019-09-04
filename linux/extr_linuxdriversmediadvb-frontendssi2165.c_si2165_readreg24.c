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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct si2165_state {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const,int) ; 
 int si2165_read (struct si2165_state*,int /*<<< orphan*/  const,int*,int) ; 

__attribute__((used)) static int si2165_readreg24(struct si2165_state *state,
			    const u16 reg, u32 *val)
{
	u8 buf[3];

	int ret = si2165_read(state, reg, buf, 3);
	*val = buf[0] | buf[1] << 8 | buf[2] << 16;
	dev_dbg(&state->client->dev, "reg read: R(0x%04x)=0x%06x\n", reg, *val);
	return ret;
}