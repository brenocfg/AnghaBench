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
typedef  int u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ENETC_TXBD_L3_SET_HSIZE (int) ; 
 int ENETC_TXBD_L3_START_MASK ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

__attribute__((used)) static inline __le16 enetc_txbd_l3_csoff(int start, int hdr_sz, u16 l3_flags)
{
	return cpu_to_le16(l3_flags | ENETC_TXBD_L3_SET_HSIZE(hdr_sz) |
			   (start & ENETC_TXBD_L3_START_MASK));
}