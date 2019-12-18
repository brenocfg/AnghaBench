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
struct nv50_disp_chan {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u64
gv100_disp_core_user(struct nv50_disp_chan *chan, u64 *psize)
{
	*psize = 0x10000;
	return 0x680000;
}