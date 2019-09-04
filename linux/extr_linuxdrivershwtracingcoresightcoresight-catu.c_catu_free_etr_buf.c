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
struct etr_buf {scalar_t__ mode; struct catu_etr_buf* private; } ;
struct catu_etr_buf {int /*<<< orphan*/  catu_table; } ;

/* Variables and functions */
 scalar_t__ ETR_MODE_CATU ; 
 int /*<<< orphan*/  kfree (struct catu_etr_buf*) ; 
 int /*<<< orphan*/  tmc_free_sg_table (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void catu_free_etr_buf(struct etr_buf *etr_buf)
{
	struct catu_etr_buf *catu_buf;

	if (!etr_buf || etr_buf->mode != ETR_MODE_CATU || !etr_buf->private)
		return;

	catu_buf = etr_buf->private;
	tmc_free_sg_table(catu_buf->catu_table);
	kfree(catu_buf);
}