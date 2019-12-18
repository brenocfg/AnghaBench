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
struct fman {int /*<<< orphan*/  fifo_size; scalar_t__ fifo_offset; int /*<<< orphan*/  muram; int /*<<< orphan*/  cam_size; scalar_t__ cam_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  fman_muram_free_mem (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_init_resources(struct fman *fman)
{
	if (fman->cam_offset)
		fman_muram_free_mem(fman->muram, fman->cam_offset,
				    fman->cam_size);
	if (fman->fifo_offset)
		fman_muram_free_mem(fman->muram, fman->fifo_offset,
				    fman->fifo_size);
}