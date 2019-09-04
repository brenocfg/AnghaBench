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
struct io_cq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_end_request; } ;
struct cfq_io_cq {TYPE_1__ ttime; } ;

/* Variables and functions */
 struct cfq_io_cq* icq_to_cic (struct io_cq*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 

__attribute__((used)) static void cfq_init_icq(struct io_cq *icq)
{
	struct cfq_io_cq *cic = icq_to_cic(icq);

	cic->ttime.last_end_request = ktime_get_ns();
}