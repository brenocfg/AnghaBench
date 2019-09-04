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
typedef  size_t u64 ;
struct etr_buf {size_t size; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_data ) (struct etr_buf*,size_t,size_t,char**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct etr_buf*,size_t,size_t,char**) ; 

__attribute__((used)) static ssize_t tmc_etr_buf_get_data(struct etr_buf *etr_buf,
				    u64 offset, size_t len, char **bufpp)
{
	/* Adjust the length to limit this transaction to end of buffer */
	len = (len < (etr_buf->size - offset)) ? len : etr_buf->size - offset;

	return etr_buf->ops->get_data(etr_buf, (u64)offset, len, bufpp);
}