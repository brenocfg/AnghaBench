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
struct wsm_buf {int /*<<< orphan*/ * end; int /*<<< orphan*/  data; int /*<<< orphan*/  begin; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void wsm_buf_deinit(struct wsm_buf *buf)
{
	kfree(buf->begin);
	buf->begin = buf->data = buf->end = NULL;
}