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
struct sdma_txreq {scalar_t__ num_desc; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sdma_txclean (struct hfi1_devdata*,struct sdma_txreq*) ; 

__attribute__((used)) static inline void sdma_txclean(struct hfi1_devdata *dd, struct sdma_txreq *tx)
{
	if (tx->num_desc)
		__sdma_txclean(dd, tx);
}