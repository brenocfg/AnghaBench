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
struct hinic_sq_wqe {TYPE_1__* buf_descs; } ;
struct hinic_sge {int dummy; } ;
typedef  int /*<<< orphan*/  sges ;
struct TYPE_2__ {struct hinic_sge sge; } ;

/* Variables and functions */
 int HINIC_MAX_SQ_BUFDESCS ; 
 int /*<<< orphan*/  hinic_be32_to_cpu (struct hinic_sge*,int) ; 

void hinic_sq_get_sges(struct hinic_sq_wqe *sq_wqe, struct hinic_sge *sges,
		       int nr_sges)
{
	int i;

	for (i = 0; i < nr_sges && i < HINIC_MAX_SQ_BUFDESCS; i++) {
		sges[i] = sq_wqe->buf_descs[i].sge;
		hinic_be32_to_cpu(&sges[i], sizeof(sges[i]));
	}
}