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
struct cxl_afu {TYPE_1__* adapter; } ;
struct TYPE_2__ {int perst_same_image; } ;

/* Variables and functions */

void cxl_perst_reloads_same_image(struct cxl_afu *afu,
				  bool perst_reloads_same_image)
{
	afu->adapter->perst_same_image = perst_reloads_same_image;
}