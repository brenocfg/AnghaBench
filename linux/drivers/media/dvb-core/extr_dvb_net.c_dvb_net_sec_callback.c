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
struct net_device {int dummy; } ;
struct dmx_section_filter {struct net_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_net_sec (struct net_device*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int dvb_net_sec_callback(const u8 *buffer1, size_t buffer1_len,
		 const u8 *buffer2, size_t buffer2_len,
		 struct dmx_section_filter *filter, u32 *buffer_flags)
{
	struct net_device *dev = filter->priv;

	/*
	 * we rely on the DVB API definition where exactly one complete
	 * section is delivered in buffer1
	 */
	dvb_net_sec (dev, buffer1, buffer1_len);
	return 0;
}