#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  timer; TYPE_1__* lmc_media; scalar_t__ lmc_ok; } ;
typedef  TYPE_2__ lmc_softc_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_link_status ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 TYPE_2__* dev_to_sc (struct net_device*) ; 
 int /*<<< orphan*/  lmc_ifdown (struct net_device*) ; 
 int /*<<< orphan*/  lmc_proto_close (TYPE_2__*) ; 
 int /*<<< orphan*/  lmc_trace (struct net_device*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lmc_close(struct net_device *dev)
{
    /* not calling release_region() as we should */
    lmc_softc_t *sc = dev_to_sc(dev);

    lmc_trace(dev, "lmc_close in");

    sc->lmc_ok = 0;
    sc->lmc_media->set_link_status (sc, 0);
    del_timer (&sc->timer);
    lmc_proto_close(sc);
    lmc_ifdown (dev);

    lmc_trace(dev, "lmc_close out");

    return 0;
}