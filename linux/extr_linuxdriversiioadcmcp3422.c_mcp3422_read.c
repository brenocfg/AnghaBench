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
struct mcp3422 {int /*<<< orphan*/  i2c; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int MCP3422_SAMPLE_RATE (int /*<<< orphan*/ ) ; 
 int MCP3422_SRATE_3 ; 
 int i2c_master_recv (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/ * mcp3422_sign_extend ; 
 int sign_extend32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp3422_read(struct mcp3422 *adc, int *value, u8 *config)
{
	int ret = 0;
	u8 sample_rate = MCP3422_SAMPLE_RATE(adc->config);
	u8 buf[4] = {0, 0, 0, 0};
	u32 temp;

	if (sample_rate == MCP3422_SRATE_3) {
		ret = i2c_master_recv(adc->i2c, buf, 4);
		temp = buf[0] << 16 | buf[1] << 8 | buf[2];
		*config = buf[3];
	} else {
		ret = i2c_master_recv(adc->i2c, buf, 3);
		temp = buf[0] << 8 | buf[1];
		*config = buf[2];
	}

	*value = sign_extend32(temp, mcp3422_sign_extend[sample_rate]);

	return ret;
}