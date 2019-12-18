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
struct yam_port {scalar_t__ rx_len; unsigned char rx_crcl; int rx_crch; unsigned char* rx_buf; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ YAM_MAX_FRAME ; 
 unsigned char* chktabh ; 
 int* chktabl ; 

__attribute__((used)) static inline void yam_rx_byte(struct net_device *dev, struct yam_port *yp, unsigned char rxb)
{
	if (yp->rx_len < YAM_MAX_FRAME) {
		unsigned char c = yp->rx_crcl;
		yp->rx_crcl = (chktabl[c] ^ yp->rx_crch);
		yp->rx_crch = (chktabh[c] ^ rxb);
		yp->rx_buf[yp->rx_len++] = rxb;
	}
}