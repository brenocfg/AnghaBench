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
struct videobuf_queue {int dummy; } ;
struct poll_table_struct {int dummy; } ;
struct omap_vout_device {struct videobuf_queue vbq; } ;
struct file {struct omap_vout_device* private_data; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  videobuf_poll_stream (struct file*,struct videobuf_queue*,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t omap_vout_poll(struct file *file,
				   struct poll_table_struct *wait)
{
	struct omap_vout_device *vout = file->private_data;
	struct videobuf_queue *q = &vout->vbq;

	return videobuf_poll_stream(file, q, wait);
}