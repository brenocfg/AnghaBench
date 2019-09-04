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
struct sge_rspq {int /*<<< orphan*/  napi; scalar_t__ handler; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void quiesce_rx(struct adapter *adap, struct sge_rspq *q)
{
	if (q && q->handler)
		napi_disable(&q->napi);
}