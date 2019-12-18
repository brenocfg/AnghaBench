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
typedef  int u32 ;

/* Variables and functions */
 int csum_none ; 
 int discard_frame ; 
 int good_frame ; 
 int llc_snap ; 

__attribute__((used)) static int enh_desc_coe_rdes0(int ipc_err, int type, int payload_err)
{
	int ret = good_frame;
	u32 status = (type << 2 | ipc_err << 1 | payload_err) & 0x7;

	/* bits 5 7 0 | Frame status
	 * ----------------------------------------------------------
	 *      0 0 0 | IEEE 802.3 Type frame (length < 1536 octects)
	 *      1 0 0 | IPv4/6 No CSUM errorS.
	 *      1 0 1 | IPv4/6 CSUM PAYLOAD error
	 *      1 1 0 | IPv4/6 CSUM IP HR error
	 *      1 1 1 | IPv4/6 IP PAYLOAD AND HEADER errorS
	 *      0 0 1 | IPv4/6 unsupported IP PAYLOAD
	 *      0 1 1 | COE bypassed.. no IPv4/6 frame
	 *      0 1 0 | Reserved.
	 */
	if (status == 0x0)
		ret = llc_snap;
	else if (status == 0x4)
		ret = good_frame;
	else if (status == 0x5)
		ret = csum_none;
	else if (status == 0x6)
		ret = csum_none;
	else if (status == 0x7)
		ret = csum_none;
	else if (status == 0x1)
		ret = discard_frame;
	else if (status == 0x3)
		ret = discard_frame;
	return ret;
}