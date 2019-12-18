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
struct vpdma_data {void** hwlist_priv; } ;

/* Variables and functions */
 int VPDMA_MAX_NUM_LIST ; 

void *vpdma_hwlist_get_priv(struct vpdma_data *vpdma, int list_num)
{
	if (!vpdma || list_num >= VPDMA_MAX_NUM_LIST)
		return NULL;

	return vpdma->hwlist_priv[list_num];
}