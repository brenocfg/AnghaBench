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
struct xgene_enet_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_FRAME_LEN_ADDR ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgene_enet_set_frame_size(struct xgene_enet_pdata *pdata, int size)
{
	xgene_enet_wr_mac(pdata, MAX_FRAME_LEN_ADDR, size);
}