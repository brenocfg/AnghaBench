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
struct etr_buf {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct etr_buf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct etr_buf*) ; 
 int /*<<< orphan*/  stub1 (struct etr_buf*) ; 

__attribute__((used)) static void tmc_free_etr_buf(struct etr_buf *etr_buf)
{
	WARN_ON(!etr_buf->ops || !etr_buf->ops->free);
	etr_buf->ops->free(etr_buf);
	kfree(etr_buf);
}