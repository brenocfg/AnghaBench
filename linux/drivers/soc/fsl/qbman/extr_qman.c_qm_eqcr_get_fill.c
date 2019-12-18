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
typedef  int u8 ;
struct qm_eqcr {int available; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;

/* Variables and functions */
 int QM_EQCR_SIZE ; 

__attribute__((used)) static inline u8 qm_eqcr_get_fill(struct qm_portal *portal)
{
	struct qm_eqcr *eqcr = &portal->eqcr;

	return QM_EQCR_SIZE - 1 - eqcr->available;
}