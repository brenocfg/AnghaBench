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
struct fsg_common {int /*<<< orphan*/ * buffhds; int /*<<< orphan*/  fsg_num_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  _fsg_common_free_buffers (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void fsg_common_free_buffers(struct fsg_common *common)
{
	_fsg_common_free_buffers(common->buffhds, common->fsg_num_buffers);
	common->buffhds = NULL;
}