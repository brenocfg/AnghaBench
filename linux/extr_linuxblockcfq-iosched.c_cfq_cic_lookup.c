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
struct io_context {int dummy; } ;
struct cfq_io_cq {int dummy; } ;
struct cfq_data {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 struct cfq_io_cq* icq_to_cic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_lookup_icq (struct io_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct cfq_io_cq *cfq_cic_lookup(struct cfq_data *cfqd,
					       struct io_context *ioc)
{
	if (ioc)
		return icq_to_cic(ioc_lookup_icq(ioc, cfqd->queue));
	return NULL;
}