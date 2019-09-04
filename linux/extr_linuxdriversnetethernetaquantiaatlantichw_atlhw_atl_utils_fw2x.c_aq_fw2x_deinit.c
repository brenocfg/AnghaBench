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
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_DEINIT ; 
 int aq_fw2x_set_link_speed (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int aq_fw2x_set_state (struct aq_hw_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aq_fw2x_deinit(struct aq_hw_s *self)
{
	int err = aq_fw2x_set_link_speed(self, 0);

	if (!err)
		err = aq_fw2x_set_state(self, MPI_DEINIT);

	return err;
}