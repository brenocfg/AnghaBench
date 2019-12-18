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
struct adv_dvc_var {int /*<<< orphan*/ * carrier; int /*<<< orphan*/  carrier_addr; } ;
struct TYPE_2__ {struct adv_dvc_var adv_dvc_var; } ;
struct asc_board {int /*<<< orphan*/ * adv_sgblk_pool; int /*<<< orphan*/ * adv_reqp; int /*<<< orphan*/  adv_reqp_addr; int /*<<< orphan*/  adv_reqp_size; int /*<<< orphan*/  dev; TYPE_1__ dvc_var; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV_CARRIER_BUFSIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void advansys_wide_free_mem(struct asc_board *board)
{
	struct adv_dvc_var *adv_dvc = &board->dvc_var.adv_dvc_var;

	if (adv_dvc->carrier) {
		dma_free_coherent(board->dev, ADV_CARRIER_BUFSIZE,
				  adv_dvc->carrier, adv_dvc->carrier_addr);
		adv_dvc->carrier = NULL;
	}
	if (board->adv_reqp) {
		dma_free_coherent(board->dev, board->adv_reqp_size,
				  board->adv_reqp, board->adv_reqp_addr);
		board->adv_reqp = NULL;
	}
	if (board->adv_sgblk_pool) {
		dma_pool_destroy(board->adv_sgblk_pool);
		board->adv_sgblk_pool = NULL;
	}
}