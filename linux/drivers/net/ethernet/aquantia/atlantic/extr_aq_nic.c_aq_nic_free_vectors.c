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
struct aq_nic_s {int /*<<< orphan*/ ** aq_vec; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  aq_vec_free (int /*<<< orphan*/ *) ; 

void aq_nic_free_vectors(struct aq_nic_s *self)
{
	unsigned int i = 0U;

	if (!self)
		goto err_exit;

	for (i = ARRAY_SIZE(self->aq_vec); i--;) {
		if (self->aq_vec[i]) {
			aq_vec_free(self->aq_vec[i]);
			self->aq_vec[i] = NULL;
		}
	}

err_exit:;
}