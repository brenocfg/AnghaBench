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
typedef  int u64 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_EVENT_TYPE_COMM_EST ; 
 int /*<<< orphan*/  MLX5_EVENT_TYPE_PATH_MIG ; 
 int /*<<< orphan*/  MLX5_EVENT_TYPE_PATH_MIG_FAILED ; 
 int /*<<< orphan*/  MLX5_EVENT_TYPE_SQ_DRAINED ; 
 int /*<<< orphan*/  MLX5_EVENT_TYPE_SRQ_LAST_WQE ; 
 int /*<<< orphan*/  MLX5_EVENT_TYPE_WQ_ACCESS_ERROR ; 
 int /*<<< orphan*/  MLX5_EVENT_TYPE_WQ_CATAS_ERROR ; 
 int /*<<< orphan*/  MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR ; 

__attribute__((used)) static u64 qp_allowed_event_types(void)
{
	u64 mask;

	mask = BIT(MLX5_EVENT_TYPE_PATH_MIG) |
	       BIT(MLX5_EVENT_TYPE_COMM_EST) |
	       BIT(MLX5_EVENT_TYPE_SQ_DRAINED) |
	       BIT(MLX5_EVENT_TYPE_SRQ_LAST_WQE) |
	       BIT(MLX5_EVENT_TYPE_WQ_CATAS_ERROR) |
	       BIT(MLX5_EVENT_TYPE_PATH_MIG_FAILED) |
	       BIT(MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR) |
	       BIT(MLX5_EVENT_TYPE_WQ_ACCESS_ERROR);

	return mask;
}