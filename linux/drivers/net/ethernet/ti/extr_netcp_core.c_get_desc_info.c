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
struct knav_dma_desc {int /*<<< orphan*/  packet_info; int /*<<< orphan*/  desc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_desc_info(u32 *desc_info, u32 *pkt_info,
			  struct knav_dma_desc *desc)
{
	*desc_info = le32_to_cpu(desc->desc_info);
	*pkt_info = le32_to_cpu(desc->packet_info);
}