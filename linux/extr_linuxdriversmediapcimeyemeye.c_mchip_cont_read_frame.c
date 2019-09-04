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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MCHIP_NB_PAGES ; 
 int /*<<< orphan*/  ptable_copy (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mchip_cont_read_frame(u32 v, u8 *buf, int size)
{
	int pt_id;

	pt_id = (v >> 17) & 0x3FF;

	ptable_copy(buf, pt_id, size, MCHIP_NB_PAGES);
}