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
typedef  int u32 ;
typedef  int u16 ;
struct ssbi {int dummy; } ;

/* Variables and functions */
 int SSBI_PA_CMD_ADDR_MASK ; 
 int ssbi_pa_transfer (struct ssbi*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ssbi_pa_write_bytes(struct ssbi *ssbi, u16 addr, const u8 *buf, int len)
{
	u32 cmd;
	int ret = 0;

	while (len) {
		cmd = (addr & SSBI_PA_CMD_ADDR_MASK) << 8 | *buf;
		ret = ssbi_pa_transfer(ssbi, cmd, NULL);
		if (ret)
			goto err;
		buf++;
		len--;
	}

err:
	return ret;
}