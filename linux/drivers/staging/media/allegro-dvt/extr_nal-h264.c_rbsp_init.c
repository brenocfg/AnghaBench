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
struct rbsp {size_t size; scalar_t__ error; struct nal_h264_ops* ops; scalar_t__ pos; void* data; } ;
struct nal_h264_ops {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void rbsp_init(struct rbsp *rbsp, void *addr, size_t size,
		      struct nal_h264_ops *ops)
{
	if (!rbsp)
		return;

	rbsp->data = addr;
	rbsp->size = size;
	rbsp->pos = 0;
	rbsp->ops = ops;
	rbsp->error = 0;
}