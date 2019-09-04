#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {int num_chan; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mbox; TYPE_1__ spu; } ;

/* Variables and functions */
 TYPE_2__ iproc_priv ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spu_mb_release(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < iproc_priv.spu.num_chan; i++)
		mbox_free_channel(iproc_priv.mbox[i]);
}