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
struct hinic_cmdq_buf {scalar_t__ size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HINIC_CMDQ_MAX_DATA_SIZE ; 

__attribute__((used)) static int cmdq_params_valid(struct hinic_cmdq_buf *buf_in)
{
	if (buf_in->size > HINIC_CMDQ_MAX_DATA_SIZE)
		return -EINVAL;

	return 0;
}