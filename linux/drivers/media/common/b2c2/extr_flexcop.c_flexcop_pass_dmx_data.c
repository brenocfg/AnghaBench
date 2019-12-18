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
typedef  int /*<<< orphan*/  u32 ;
struct flexcop_device {int /*<<< orphan*/  demux; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void flexcop_pass_dmx_data(struct flexcop_device *fc, u8 *buf, u32 len)
{
	dvb_dmx_swfilter(&fc->demux, buf, len);
}