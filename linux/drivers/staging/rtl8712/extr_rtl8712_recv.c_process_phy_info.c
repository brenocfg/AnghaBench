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
typedef  union recv_frame {int dummy; } recv_frame ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  process_link_qual (struct _adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  process_rssi (struct _adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  query_rx_phy_status (struct _adapter*,union recv_frame*) ; 

__attribute__((used)) static void process_phy_info(struct _adapter *padapter,
			     union recv_frame *prframe)
{
	query_rx_phy_status(padapter, prframe);
	process_rssi(padapter, prframe);
	process_link_qual(padapter,  prframe);
}