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
struct sdma_engine {int /*<<< orphan*/  cpu; TYPE_1__* dd; } ;
struct iowait {int dummy; } ;
struct hfi1_pportdata {int /*<<< orphan*/  hfi1_wq; } ;
struct TYPE_2__ {struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowait_schedule (struct iowait*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sdma_iowait_schedule(
	struct sdma_engine *sde,
	struct iowait *wait)
{
	struct hfi1_pportdata *ppd = sde->dd->pport;

	iowait_schedule(wait, ppd->hfi1_wq, sde->cpu);
}