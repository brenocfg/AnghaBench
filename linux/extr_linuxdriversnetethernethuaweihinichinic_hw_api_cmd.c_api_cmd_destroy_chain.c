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
struct hinic_api_cmd_chain {int /*<<< orphan*/  num_cells; } ;

/* Variables and functions */
 int /*<<< orphan*/  api_chain_free (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  api_cmd_chain_hw_clean (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  api_cmd_destroy_cells (struct hinic_api_cmd_chain*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void api_cmd_destroy_chain(struct hinic_api_cmd_chain *chain)
{
	api_cmd_chain_hw_clean(chain);
	api_cmd_destroy_cells(chain, chain->num_cells);
	api_chain_free(chain);
}