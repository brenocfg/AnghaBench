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
struct stk_sio_buffer {int dummy; } ;
struct stk_camera {int n_sbufs; int /*<<< orphan*/ * sio_bufs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ stk_setup_siobuf (struct stk_camera*,int) ; 

__attribute__((used)) static int stk_prepare_sio_buffers(struct stk_camera *dev, unsigned n_sbufs)
{
	int i;
	if (dev->sio_bufs != NULL)
		pr_err("sio_bufs already allocated\n");
	else {
		dev->sio_bufs = kcalloc(n_sbufs,
					sizeof(struct stk_sio_buffer),
					GFP_KERNEL);
		if (dev->sio_bufs == NULL)
			return -ENOMEM;
		for (i = 0; i < n_sbufs; i++) {
			if (stk_setup_siobuf(dev, i))
				return (dev->n_sbufs > 1 ? 0 : -ENOMEM);
			dev->n_sbufs = i+1;
		}
	}
	return 0;
}