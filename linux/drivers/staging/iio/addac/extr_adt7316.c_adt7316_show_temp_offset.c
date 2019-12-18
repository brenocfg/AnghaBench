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
struct TYPE_2__ {int (* read ) (int /*<<< orphan*/ ,int,int*) ;int /*<<< orphan*/  client; } ;
struct adt7316_chip_info {TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static ssize_t adt7316_show_temp_offset(struct adt7316_chip_info *chip,
					int offset_addr, char *buf)
{
	int data;
	u8 val;
	int ret;

	ret = chip->bus.read(chip->bus.client, offset_addr, &val);
	if (ret)
		return -EIO;

	data = (int)val;
	if (val & 0x80)
		data -= 256;

	return sprintf(buf, "%d\n", data);
}