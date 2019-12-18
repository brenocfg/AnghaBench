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
typedef  int /*<<< orphan*/  u32 ;
struct hw_atl_utils_mbox_header {int /*<<< orphan*/  transaction_id; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_atl_utils_mpi_read_mbox (struct aq_hw_s*,struct hw_atl_utils_mbox_header*) ; 

__attribute__((used)) static u32 hw_atl_utils_get_mpi_mbox_tid(struct aq_hw_s *self)
{
	struct hw_atl_utils_mbox_header mbox;

	hw_atl_utils_mpi_read_mbox(self, &mbox);

	return mbox.transaction_id;
}