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
struct rvu {int /*<<< orphan*/  dev; } ;
struct admin_queue {int /*<<< orphan*/  res; int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct admin_queue*) ; 
 int /*<<< orphan*/  qmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rvu_aq_free(struct rvu *rvu, struct admin_queue *aq)
{
	if (!aq)
		return;

	qmem_free(rvu->dev, aq->inst);
	qmem_free(rvu->dev, aq->res);
	devm_kfree(rvu->dev, aq);
}