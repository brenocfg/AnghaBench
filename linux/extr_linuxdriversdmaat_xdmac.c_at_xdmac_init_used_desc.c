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
struct at_xdmac_desc {int active_xfer; scalar_t__ xfer_size; int /*<<< orphan*/  direction; int /*<<< orphan*/  descs_list; int /*<<< orphan*/  lld; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TRANS_NONE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at_xdmac_init_used_desc(struct at_xdmac_desc *desc)
{
	memset(&desc->lld, 0, sizeof(desc->lld));
	INIT_LIST_HEAD(&desc->descs_list);
	desc->direction = DMA_TRANS_NONE;
	desc->xfer_size = 0;
	desc->active_xfer = false;
}