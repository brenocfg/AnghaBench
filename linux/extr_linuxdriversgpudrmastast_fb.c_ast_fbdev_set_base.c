#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ast_private {scalar_t__ vram_size; TYPE_6__* fbdev; } ;
struct TYPE_10__ {TYPE_5__* fbdev; } ;
struct TYPE_12__ {TYPE_4__ helper; } ;
struct TYPE_7__ {scalar_t__ smem_len; scalar_t__ smem_start; } ;
struct TYPE_11__ {TYPE_1__ fix; TYPE_3__* apertures; } ;
struct TYPE_9__ {TYPE_2__* ranges; } ;
struct TYPE_8__ {scalar_t__ base; } ;

/* Variables and functions */

void ast_fbdev_set_base(struct ast_private *ast, unsigned long gpu_addr)
{
	ast->fbdev->helper.fbdev->fix.smem_start =
		ast->fbdev->helper.fbdev->apertures->ranges[0].base + gpu_addr;
	ast->fbdev->helper.fbdev->fix.smem_len = ast->vram_size - gpu_addr;
}