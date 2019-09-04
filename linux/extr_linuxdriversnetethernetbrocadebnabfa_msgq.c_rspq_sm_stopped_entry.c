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
struct bfa_msgq_rspq {scalar_t__ flags; scalar_t__ consumer_index; scalar_t__ producer_index; } ;

/* Variables and functions */

__attribute__((used)) static void
rspq_sm_stopped_entry(struct bfa_msgq_rspq *rspq)
{
	rspq->producer_index = 0;
	rspq->consumer_index = 0;
	rspq->flags = 0;
}