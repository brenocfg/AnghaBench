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
struct cfv_info {int /*<<< orphan*/  vq_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfv_release_used_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfv_tx_release_tasklet(unsigned long drv)
{
	struct cfv_info *cfv = (struct cfv_info *)drv;
	cfv_release_used_buf(cfv->vq_tx);
}