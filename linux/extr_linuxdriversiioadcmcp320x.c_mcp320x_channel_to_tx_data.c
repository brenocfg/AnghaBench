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

/* Variables and functions */
 int EINVAL ; 
#define  mcp3002 133 
#define  mcp3004 132 
#define  mcp3008 131 
#define  mcp3202 130 
#define  mcp3204 129 
#define  mcp3208 128 

__attribute__((used)) static int mcp320x_channel_to_tx_data(int device_index,
			const unsigned int channel, bool differential)
{
	int start_bit = 1;

	switch (device_index) {
	case mcp3002:
	case mcp3202:
		return ((start_bit << 4) | (!differential << 3) |
							(channel << 2));
	case mcp3004:
	case mcp3204:
	case mcp3008:
	case mcp3208:
		return ((start_bit << 6) | (!differential << 5) |
							(channel << 2));
	default:
		return -EINVAL;
	}
}