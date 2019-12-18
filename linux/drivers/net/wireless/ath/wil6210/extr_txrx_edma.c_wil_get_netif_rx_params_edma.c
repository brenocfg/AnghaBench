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
struct wil_rx_status_extended {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int wil_rx_status_get_cid (struct wil_rx_status_extended*) ; 
 int wil_rx_status_get_security (struct wil_rx_status_extended*) ; 
 struct wil_rx_status_extended* wil_skb_rxstatus (struct sk_buff*) ; 

__attribute__((used)) static void wil_get_netif_rx_params_edma(struct sk_buff *skb, int *cid,
					 int *security)
{
	struct wil_rx_status_extended *s = wil_skb_rxstatus(skb);

	*cid = wil_rx_status_get_cid(s);
	*security = wil_rx_status_get_security(s);
}