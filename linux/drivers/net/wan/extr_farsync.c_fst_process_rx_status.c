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

/* Variables and functions */
 int /*<<< orphan*/  DBG_ASS ; 
#define  NET_RX_DROP 129 
#define  NET_RX_SUCCESS 128 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
fst_process_rx_status(int rx_status, char *name)
{
	switch (rx_status) {
	case NET_RX_SUCCESS:
		{
			/*
			 * Nothing to do here
			 */
			break;
		}
	case NET_RX_DROP:
		{
			dbg(DBG_ASS, "%s: Received packet dropped\n", name);
			break;
		}
	}
}