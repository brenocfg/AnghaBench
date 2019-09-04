#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ transcnt; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MInit_dialin ; 
 int /*<<< orphan*/  MInit_dialout ; 
 int /*<<< orphan*/  MInit_speed28800 ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  modem_write_cmd (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
modem_set_dial(struct IsdnCardState *cs, int outgoing) {
	int timeout;
#define RCV_DELAY 20

	modem_write_cmd(cs, MInit_speed28800, strlen(MInit_speed28800));
	timeout = 1000;
	while (timeout-- && cs->hw.elsa.transcnt)
		udelay(1000);
	debugl1(cs, "msi tout=%d", timeout);
	mdelay(RCV_DELAY);
	if (outgoing)
		modem_write_cmd(cs, MInit_dialout, strlen(MInit_dialout));
	else
		modem_write_cmd(cs, MInit_dialin, strlen(MInit_dialin));
	timeout = 1000;
	while (timeout-- && cs->hw.elsa.transcnt)
		udelay(1000);
	debugl1(cs, "msi tout=%d", timeout);
	mdelay(RCV_DELAY);
}