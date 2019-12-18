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
typedef  void* u8 ;
typedef  int u32 ;
struct xps2data {scalar_t__ base_address; } ;

/* Variables and functions */
 scalar_t__ XPS2_RX_DATA_OFFSET ; 
 scalar_t__ XPS2_STATUS_OFFSET ; 
 int XPS2_STATUS_RX_FULL ; 
 void* in_be32 (scalar_t__) ; 

__attribute__((used)) static int xps2_recv(struct xps2data *drvdata, u8 *byte)
{
	u32 sr;
	int status = -1;

	/* If there is data available in the PS/2 receiver, read it */
	sr = in_be32(drvdata->base_address + XPS2_STATUS_OFFSET);
	if (sr & XPS2_STATUS_RX_FULL) {
		*byte = in_be32(drvdata->base_address + XPS2_RX_DATA_OFFSET);
		status = 0;
	}

	return status;
}