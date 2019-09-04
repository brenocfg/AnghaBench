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
struct sun4i_dma_contract {int /*<<< orphan*/  completed_demands; int /*<<< orphan*/  demands; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct sun4i_dma_contract* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sun4i_dma_contract *generate_dma_contract(void)
{
	struct sun4i_dma_contract *contract;

	contract = kzalloc(sizeof(*contract), GFP_NOWAIT);
	if (!contract)
		return NULL;

	INIT_LIST_HEAD(&contract->demands);
	INIT_LIST_HEAD(&contract->completed_demands);

	return contract;
}