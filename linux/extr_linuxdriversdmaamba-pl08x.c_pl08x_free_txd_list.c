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
struct pl08x_driver_data {int dummy; } ;
struct pl08x_dma_chan {int /*<<< orphan*/  vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pl08x_free_txd_list(struct pl08x_driver_data *pl08x,
				struct pl08x_dma_chan *plchan)
{
	LIST_HEAD(head);

	vchan_get_all_descriptors(&plchan->vc, &head);
	vchan_dma_desc_free_list(&plchan->vc, &head);
}