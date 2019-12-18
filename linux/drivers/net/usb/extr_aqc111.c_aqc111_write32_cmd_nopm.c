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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  tmp ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int aqc111_write_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32s (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aqc111_write32_cmd_nopm(struct usbnet *dev, u8 cmd, u16 value,
				   u16 index, u32 *data)
{
	u32 tmp = *data;

	cpu_to_le32s(&tmp);

	return aqc111_write_cmd_nopm(dev, cmd, value, index, sizeof(tmp), &tmp);
}