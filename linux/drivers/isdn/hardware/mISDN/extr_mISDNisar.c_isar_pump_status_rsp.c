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
struct isar_ch {int /*<<< orphan*/  conmsg; TYPE_1__* is; } ;
struct TYPE_2__ {int* buf; int /*<<< orphan*/  name; int /*<<< orphan*/  Flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISAR_RATE_REQ ; 
 char** dmril ; 
 char** dmrim ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isar_pump_status_rsp(struct isar_ch *ch) {
	u8 ril = ch->is->buf[0];
	u8 rim;

	if (!test_and_clear_bit(ISAR_RATE_REQ, &ch->is->Flags))
		return;
	if (ril > 14) {
		pr_info("%s: wrong pstrsp ril=%d\n", ch->is->name, ril);
		ril = 15;
	}
	switch (ch->is->buf[1]) {
	case 0:
		rim = 0;
		break;
	case 0x20:
		rim = 2;
		break;
	case 0x40:
		rim = 3;
		break;
	case 0x41:
		rim = 4;
		break;
	case 0x51:
		rim = 5;
		break;
	case 0x61:
		rim = 6;
		break;
	case 0x71:
		rim = 7;
		break;
	case 0x82:
		rim = 8;
		break;
	case 0x92:
		rim = 9;
		break;
	case 0xa2:
		rim = 10;
		break;
	default:
		rim = 1;
		break;
	}
	sprintf(ch->conmsg, "%s %s", dmril[ril], dmrim[rim]);
	pr_debug("%s: pump strsp %s\n", ch->is->name, ch->conmsg);
}