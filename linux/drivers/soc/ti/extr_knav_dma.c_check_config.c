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
struct knav_dma_chan {int /*<<< orphan*/  cfg; } ;
struct knav_dma_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,struct knav_dma_cfg*,int) ; 

__attribute__((used)) static bool check_config(struct knav_dma_chan *chan, struct knav_dma_cfg *cfg)
{
	if (!memcmp(&chan->cfg, cfg, sizeof(*cfg)))
		return true;
	else
		return false;
}