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
typedef  int u8 ;
struct steam_device {int /*<<< orphan*/  serial_no; } ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EIO ; 
 int STEAM_CMD_GET_SERIAL ; 
 int STEAM_SERIAL_LEN ; 
 int steam_recv_report (struct steam_device*,int*,int) ; 
 int steam_send_report (struct steam_device*,int*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int steam_get_serial(struct steam_device *steam)
{
	/*
	 * Send: 0xae 0x15 0x01
	 * Recv: 0xae 0x15 0x01 serialnumber (10 chars)
	 */
	int ret;
	u8 cmd[] = {STEAM_CMD_GET_SERIAL, 0x15, 0x01};
	u8 reply[3 + STEAM_SERIAL_LEN + 1];

	ret = steam_send_report(steam, cmd, sizeof(cmd));
	if (ret < 0)
		return ret;
	ret = steam_recv_report(steam, reply, sizeof(reply));
	if (ret < 0)
		return ret;
	if (reply[0] != 0xae || reply[1] != 0x15 || reply[2] != 0x01)
		return -EIO;
	reply[3 + STEAM_SERIAL_LEN] = 0;
	strlcpy(steam->serial_no, reply + 3, sizeof(steam->serial_no));
	return 0;
}