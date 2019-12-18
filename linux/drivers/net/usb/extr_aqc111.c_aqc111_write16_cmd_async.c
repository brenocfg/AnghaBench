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
typedef  int /*<<< orphan*/  tmp ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int aqc111_write_cmd_async (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16s (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aqc111_write16_cmd_async(struct usbnet *dev, u8 cmd, u16 value,
				    u16 index, u16 *data)
{
	u16 tmp = *data;

	cpu_to_le16s(&tmp);

	return aqc111_write_cmd_async(dev, cmd, value, index,
				      sizeof(tmp), &tmp);
}