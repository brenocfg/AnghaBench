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
struct vb2_dc_buf {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 unsigned int refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int vb2_dc_num_users(void *buf_priv)
{
	struct vb2_dc_buf *buf = buf_priv;

	return refcount_read(&buf->refcount);
}