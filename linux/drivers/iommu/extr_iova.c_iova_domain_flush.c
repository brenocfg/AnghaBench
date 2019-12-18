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
struct iova_domain {int /*<<< orphan*/  fq_flush_finish_cnt; int /*<<< orphan*/  (* flush_cb ) (struct iova_domain*) ;int /*<<< orphan*/  fq_flush_start_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iova_domain*) ; 

__attribute__((used)) static void iova_domain_flush(struct iova_domain *iovad)
{
	atomic64_inc(&iovad->fq_flush_start_cnt);
	iovad->flush_cb(iovad);
	atomic64_inc(&iovad->fq_flush_finish_cnt);
}