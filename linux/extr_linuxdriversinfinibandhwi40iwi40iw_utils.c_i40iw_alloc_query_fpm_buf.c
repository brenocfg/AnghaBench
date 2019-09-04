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
struct i40iw_sc_dev {scalar_t__ back_dev; } ;
struct i40iw_dma_mem {int dummy; } ;
struct i40iw_device {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_FPM_QUERY_BUF_ALIGNMENT_MASK ; 
 int /*<<< orphan*/  I40IW_QUERY_FPM_BUF_SIZE ; 
 int i40iw_obj_aligned_mem (struct i40iw_device*,struct i40iw_dma_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum i40iw_status_code i40iw_alloc_query_fpm_buf(struct i40iw_sc_dev *dev,
						 struct i40iw_dma_mem *mem)
{
	enum i40iw_status_code status;
	struct i40iw_device *iwdev = (struct i40iw_device *)dev->back_dev;

	status = i40iw_obj_aligned_mem(iwdev, mem, I40IW_QUERY_FPM_BUF_SIZE,
				       I40IW_FPM_QUERY_BUF_ALIGNMENT_MASK);
	return status;
}