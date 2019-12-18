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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCP795_EXTOSC_BIT ; 
 int /*<<< orphan*/  MCP795_REG_CONTROL ; 
 int /*<<< orphan*/  MCP795_REG_SECONDS ; 
 int /*<<< orphan*/  MCP795_ST_BIT ; 
 int mcp795_rtcc_set_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp795_start_oscillator(struct device *dev, bool *extosc)
{
	if (extosc) {
		u8 data = *extosc ? MCP795_EXTOSC_BIT : 0;
		int ret;

		ret = mcp795_rtcc_set_bits(
			dev, MCP795_REG_CONTROL, MCP795_EXTOSC_BIT, data);
		if (ret)
			return ret;
	}
	return mcp795_rtcc_set_bits(
			dev, MCP795_REG_SECONDS, MCP795_ST_BIT, MCP795_ST_BIT);
}