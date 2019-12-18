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
struct steam_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STEAM_CMD_REQUEST_COMM_STATUS ; 
 int steam_send_report_byte (struct steam_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int steam_request_conn_status(struct steam_device *steam)
{
	return steam_send_report_byte(steam, STEAM_CMD_REQUEST_COMM_STATUS);
}