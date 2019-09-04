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
struct aiptek {TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int aiptek_set_report (struct aiptek*,int,int,int*,int const) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aiptek_command(struct aiptek *aiptek, unsigned char command, unsigned char data)
{
	const int sizeof_buf = 3 * sizeof(u8);
	int ret;
	u8 *buf;

	buf = kmalloc(sizeof_buf, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf[0] = 2;
	buf[1] = command;
	buf[2] = data;

	if ((ret =
	     aiptek_set_report(aiptek, 3, 2, buf, sizeof_buf)) != sizeof_buf) {
		dev_dbg(&aiptek->intf->dev,
			"aiptek_program: failed, tried to send: 0x%02x 0x%02x\n",
			command, data);
	}
	kfree(buf);
	return ret < 0 ? ret : 0;
}