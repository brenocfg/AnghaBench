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
struct TYPE_2__ {char** fw; } ;

/* Variables and functions */
 TYPE_1__* sms_get_board (int) ; 
 char** smsusb1_fw_lkup ; 

__attribute__((used)) static inline char *sms_get_fw_name(int mode, int board_id)
{
	char **fw = sms_get_board(board_id)->fw;
	return (fw && fw[mode]) ? fw[mode] : smsusb1_fw_lkup[mode];
}