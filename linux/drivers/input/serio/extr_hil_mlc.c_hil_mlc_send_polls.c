#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct serio_driver {int /*<<< orphan*/  (* interrupt ) (struct serio*,int,int /*<<< orphan*/ ) ;} ;
struct serio {struct serio_driver* drv; } ;
typedef  int hil_packet ;
struct TYPE_3__ {int* ipacket; size_t* di_map; int icount; struct serio** serio; } ;
typedef  TYPE_1__ hil_mlc ;

/* Variables and functions */
 int HIL_CMD_POL ; 
 int HIL_ERR_INT ; 
 int HIL_PKT_ADDR_MASK ; 
 int HIL_PKT_CMD ; 
 int /*<<< orphan*/  stub1 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct serio*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hil_mlc_send_polls(hil_mlc *mlc)
{
	int did, i, cnt;
	struct serio *serio;
	struct serio_driver *drv;

	i = cnt = 0;
	did = (mlc->ipacket[0] & HIL_PKT_ADDR_MASK) >> 8;
	serio = did ? mlc->serio[mlc->di_map[did - 1]] : NULL;
	drv = (serio != NULL) ? serio->drv : NULL;

	while (mlc->icount < 15 - i) {
		hil_packet p;

		p = mlc->ipacket[i];
		if (did != (p & HIL_PKT_ADDR_MASK) >> 8) {
			if (drv && drv->interrupt) {
				drv->interrupt(serio, 0, 0);
				drv->interrupt(serio, HIL_ERR_INT >> 16, 0);
				drv->interrupt(serio, HIL_PKT_CMD >> 8,  0);
				drv->interrupt(serio, HIL_CMD_POL + cnt, 0);
			}

			did = (p & HIL_PKT_ADDR_MASK) >> 8;
			serio = did ? mlc->serio[mlc->di_map[did-1]] : NULL;
			drv = (serio != NULL) ? serio->drv : NULL;
			cnt = 0;
		}

		cnt++;
		i++;

		if (drv && drv->interrupt) {
			drv->interrupt(serio, (p >> 24), 0);
			drv->interrupt(serio, (p >> 16) & 0xff, 0);
			drv->interrupt(serio, (p >> 8) & ~HIL_PKT_ADDR_MASK, 0);
			drv->interrupt(serio, p & 0xff, 0);
		}
	}
}