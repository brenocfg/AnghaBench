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
struct recv_frame {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  process_link_qual (struct adapter*,struct recv_frame*) ; 
 int /*<<< orphan*/  process_rssi (struct adapter*,struct recv_frame*) ; 

void rtl8188e_process_phy_info(struct adapter *padapter,
			       struct recv_frame *precvframe)
{
	/*  Check RSSI */
	process_rssi(padapter, precvframe);
	/*  Check EVM */
	process_link_qual(padapter,  precvframe);
}