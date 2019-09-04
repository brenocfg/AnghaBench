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
typedef  int u16 ;
struct input_dev {int dummy; } ;
struct iforce {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_CMD_AUTOCENTER ; 
 int /*<<< orphan*/  iforce_send_packet (struct iforce*,int /*<<< orphan*/ ,unsigned char*) ; 
 struct iforce* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void iforce_set_autocenter(struct input_dev *dev, u16 magnitude)
{
	struct iforce *iforce = input_get_drvdata(dev);
	unsigned char data[3];

	data[0] = 0x03;
	data[1] = magnitude >> 9;
	iforce_send_packet(iforce, FF_CMD_AUTOCENTER, data);

	data[0] = 0x04;
	data[1] = 0x01;
	iforce_send_packet(iforce, FF_CMD_AUTOCENTER, data);
}