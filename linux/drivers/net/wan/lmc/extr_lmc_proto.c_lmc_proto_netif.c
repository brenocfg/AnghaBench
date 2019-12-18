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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int if_type; int /*<<< orphan*/  lmc_device; } ;
typedef  TYPE_1__ lmc_softc_t ;

/* Variables and functions */
#define  LMC_NET 130 
#define  LMC_PPP 129 
#define  LMC_RAW 128 
 int /*<<< orphan*/  lmc_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

void lmc_proto_netif(lmc_softc_t *sc, struct sk_buff *skb) /*FOLD00*/
{
    lmc_trace(sc->lmc_device, "lmc_proto_netif in");
    switch(sc->if_type){
    case LMC_PPP:
    case LMC_NET:
    default:
        netif_rx(skb);
        break;
    case LMC_RAW:
        break;
    }
    lmc_trace(sc->lmc_device, "lmc_proto_netif out");
}