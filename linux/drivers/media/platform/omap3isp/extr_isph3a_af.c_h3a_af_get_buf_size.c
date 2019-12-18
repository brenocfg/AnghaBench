#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int h_cnt; int v_cnt; } ;
struct omap3isp_h3a_af_config {TYPE_1__ paxel; } ;

/* Variables and functions */
 int OMAP3ISP_AF_PAXEL_SIZE ; 

__attribute__((used)) static u32 h3a_af_get_buf_size(struct omap3isp_h3a_af_config *conf)
{
	return conf->paxel.h_cnt * conf->paxel.v_cnt * OMAP3ISP_AF_PAXEL_SIZE;
}