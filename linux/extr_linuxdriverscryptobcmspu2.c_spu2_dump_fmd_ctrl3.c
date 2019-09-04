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
typedef  int u64 ;

/* Variables and functions */
 int SPU2_PL_LEN ; 
 int SPU2_TLS_LEN ; 
 int SPU2_TLS_LEN_SHIFT ; 
 int /*<<< orphan*/  packet_log (char*,int) ; 

__attribute__((used)) static void spu2_dump_fmd_ctrl3(u64 ctrl3)
{
	packet_log(" FMD CTRL3 %#16llx\n", ctrl3);

	packet_log("  Payload length %llu bytes\n", ctrl3 & SPU2_PL_LEN);
	packet_log("  TLS length %llu bytes\n",
		   (ctrl3 & SPU2_TLS_LEN) >> SPU2_TLS_LEN_SHIFT);
}