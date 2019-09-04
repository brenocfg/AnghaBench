#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct h_epa {int dummy; } ;
struct TYPE_2__ {struct h_epa kernel; } ;
struct ehea_cq {TYPE_1__ epas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQTEMM_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CQX_EP_EVENT_PENDING ; 
 int /*<<< orphan*/  EHEA_BMASK_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqx_ep ; 
 int /*<<< orphan*/  epa_store_acc (struct h_epa,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ehea_reset_cq_ep(struct ehea_cq *my_cq)
{
	struct h_epa epa = my_cq->epas.kernel;
	epa_store_acc(epa, CQTEMM_OFFSET(cqx_ep),
		      EHEA_BMASK_SET(CQX_EP_EVENT_PENDING, 0));
}