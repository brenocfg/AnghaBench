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
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct dw_dma_chan {TYPE_1__ active_list; } ;
struct dw_desc {int dummy; } ;

/* Variables and functions */
 struct dw_desc* to_dw_desc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dw_desc *dwc_first_active(struct dw_dma_chan *dwc)
{
	return to_dw_desc(dwc->active_list.next);
}