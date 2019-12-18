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
struct falcon_board {int dummy; } ;
struct falcon_nic_data {struct falcon_board board; } ;
struct ef4_nic {struct falcon_nic_data* nic_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct falcon_board *falcon_board(struct ef4_nic *efx)
{
	struct falcon_nic_data *data = efx->nic_data;
	return &data->board;
}