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
typedef  int /*<<< orphan*/  u32 ;
struct knav_dma_desc {void* packet_info; void* desc_info; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_desc_info(u32 desc_info, u32 pkt_info,
			  struct knav_dma_desc *desc)
{
	desc->desc_info = cpu_to_le32(desc_info);
	desc->packet_info = cpu_to_le32(pkt_info);
}