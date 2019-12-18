#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {size_t size; TYPE_2__* queue; } ;
struct t4_wq {TYPE_3__ sq; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_wq_pidx; } ;
struct TYPE_5__ {TYPE_1__ status; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 t4_sq_host_wq_pidx(struct t4_wq *wq)
{
	return wq->sq.queue[wq->sq.size].status.host_wq_pidx;
}