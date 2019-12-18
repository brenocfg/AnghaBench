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
struct scif_copy_work {int /*<<< orphan*/  remote_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  scif_iounmap (void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
iounmap_remote(void *virt, size_t size, struct scif_copy_work *work)
{
	scif_iounmap(virt, size, work->remote_dev);
}