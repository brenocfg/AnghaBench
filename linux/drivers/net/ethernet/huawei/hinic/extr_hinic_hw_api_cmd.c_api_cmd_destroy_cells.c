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
struct hinic_api_cmd_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  api_cmd_destroy_cell (struct hinic_api_cmd_chain*,int) ; 

__attribute__((used)) static void api_cmd_destroy_cells(struct hinic_api_cmd_chain *chain,
				  int num_cells)
{
	int cell_idx;

	for (cell_idx = 0; cell_idx < num_cells; cell_idx++)
		api_cmd_destroy_cell(chain, cell_idx);
}