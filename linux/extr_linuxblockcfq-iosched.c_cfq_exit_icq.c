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
struct io_cq {int dummy; } ;
struct cfq_io_cq {int dummy; } ;
struct cfq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfq_exit_cfqq (struct cfq_data*,scalar_t__) ; 
 int /*<<< orphan*/  cic_set_cfqq (struct cfq_io_cq*,int /*<<< orphan*/ *,int) ; 
 struct cfq_data* cic_to_cfqd (struct cfq_io_cq*) ; 
 scalar_t__ cic_to_cfqq (struct cfq_io_cq*,int) ; 
 struct cfq_io_cq* icq_to_cic (struct io_cq*) ; 

__attribute__((used)) static void cfq_exit_icq(struct io_cq *icq)
{
	struct cfq_io_cq *cic = icq_to_cic(icq);
	struct cfq_data *cfqd = cic_to_cfqd(cic);

	if (cic_to_cfqq(cic, false)) {
		cfq_exit_cfqq(cfqd, cic_to_cfqq(cic, false));
		cic_set_cfqq(cic, NULL, false);
	}

	if (cic_to_cfqq(cic, true)) {
		cfq_exit_cfqq(cfqd, cic_to_cfqq(cic, true));
		cic_set_cfqq(cic, NULL, true);
	}
}