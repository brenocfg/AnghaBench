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
struct lpfc_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_sli4_queue_free (struct lpfc_queue*) ; 

__attribute__((used)) static inline void
__lpfc_sli4_release_queue(struct lpfc_queue **qp)
{
	if (*qp != NULL) {
		lpfc_sli4_queue_free(*qp);
		*qp = NULL;
	}
}