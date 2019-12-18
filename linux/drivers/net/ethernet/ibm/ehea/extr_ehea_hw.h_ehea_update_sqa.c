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
typedef  int /*<<< orphan*/  u16 ;
struct h_epa {int dummy; } ;
struct TYPE_2__ {struct h_epa kernel; } ;
struct ehea_qp {TYPE_1__ epas; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_BMASK_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QPTEMM_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QPX_SQA_VALUE ; 
 int /*<<< orphan*/  epa_store_acc (struct h_epa,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qpx_sqa ; 

__attribute__((used)) static inline void ehea_update_sqa(struct ehea_qp *qp, u16 nr_wqes)
{
	struct h_epa epa = qp->epas.kernel;
	epa_store_acc(epa, QPTEMM_OFFSET(qpx_sqa),
		      EHEA_BMASK_SET(QPX_SQA_VALUE, nr_wqes));
}