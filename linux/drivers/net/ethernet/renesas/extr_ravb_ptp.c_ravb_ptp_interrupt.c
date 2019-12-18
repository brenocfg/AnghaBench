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
typedef  int u32 ;
struct ravb_ptp_perout {int /*<<< orphan*/  target; scalar_t__ period; } ;
struct TYPE_2__ {struct ravb_ptp_perout* perout; int /*<<< orphan*/  clock; } ;
struct ravb_private {TYPE_1__ ptp; } ;
struct ptp_clock_event {int timestamp; scalar_t__ index; int /*<<< orphan*/  type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCPT ; 
 int /*<<< orphan*/  GIC ; 
 int /*<<< orphan*/  GIS ; 
 int GIS_PTCF ; 
 int GIS_PTMF ; 
 int GIS_RESERVED ; 
 int /*<<< orphan*/  PTP_CLOCK_EXTTS ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ptp_clock_event (int /*<<< orphan*/ ,struct ptp_clock_event*) ; 
 int /*<<< orphan*/  ravb_ptp_update_compare (struct ravb_private*,int /*<<< orphan*/ ) ; 
 int ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int,int /*<<< orphan*/ ) ; 

void ravb_ptp_interrupt(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	u32 gis = ravb_read(ndev, GIS);

	gis &= ravb_read(ndev, GIC);
	if (gis & GIS_PTCF) {
		struct ptp_clock_event event;

		event.type = PTP_CLOCK_EXTTS;
		event.index = 0;
		event.timestamp = ravb_read(ndev, GCPT);
		ptp_clock_event(priv->ptp.clock, &event);
	}
	if (gis & GIS_PTMF) {
		struct ravb_ptp_perout *perout = priv->ptp.perout;

		if (perout->period) {
			perout->target += perout->period;
			ravb_ptp_update_compare(priv, perout->target);
		}
	}

	ravb_write(ndev, ~(gis | GIS_RESERVED), GIS);
}