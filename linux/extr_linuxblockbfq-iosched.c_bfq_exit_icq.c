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
struct bfq_io_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_exit_icq_bfqq (struct bfq_io_cq*,int) ; 
 struct bfq_io_cq* icq_to_bic (struct io_cq*) ; 

__attribute__((used)) static void bfq_exit_icq(struct io_cq *icq)
{
	struct bfq_io_cq *bic = icq_to_bic(icq);

	bfq_exit_icq_bfqq(bic, true);
	bfq_exit_icq_bfqq(bic, false);
}