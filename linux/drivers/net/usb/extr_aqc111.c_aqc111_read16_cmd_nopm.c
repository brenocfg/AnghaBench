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
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int aqc111_read_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aqc111_read16_cmd_nopm(struct usbnet *dev, u8 cmd, u16 value,
				  u16 index, u16 *data)
{
	int ret = 0;

	ret = aqc111_read_cmd_nopm(dev, cmd, value, index, sizeof(*data), data);
	le16_to_cpus(data);

	return ret;
}