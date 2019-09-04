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
struct i2c_client {int dummy; } ;
struct fsa9480_usbsw {struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  FSA9480_REG_MANSW1 ; 
 unsigned int SW_AUDIO ; 
 unsigned int SW_AUTO ; 
 unsigned int SW_DHOST ; 
 unsigned int SW_UART ; 
 unsigned int SW_VAUDIO ; 
 struct fsa9480_usbsw* chip ; 
 unsigned int fsa9480_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t fsa9480_get_switch(char *buf)
{
	struct fsa9480_usbsw *usbsw = chip;
	struct i2c_client *client = usbsw->client;
	unsigned int value;

	value = fsa9480_read_reg(client, FSA9480_REG_MANSW1);

	if (value == SW_VAUDIO)
		return sprintf(buf, "VAUDIO\n");
	else if (value == SW_UART)
		return sprintf(buf, "UART\n");
	else if (value == SW_AUDIO)
		return sprintf(buf, "AUDIO\n");
	else if (value == SW_DHOST)
		return sprintf(buf, "DHOST\n");
	else if (value == SW_AUTO)
		return sprintf(buf, "AUTO\n");
	else
		return sprintf(buf, "%x", value);
}