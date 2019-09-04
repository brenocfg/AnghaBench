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
struct fman_mac {struct fman_mac* dtsec_drv_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_init_resources (struct fman_mac*) ; 
 int /*<<< orphan*/  kfree (struct fman_mac*) ; 

int dtsec_free(struct fman_mac *dtsec)
{
	free_init_resources(dtsec);

	kfree(dtsec->dtsec_drv_param);
	dtsec->dtsec_drv_param = NULL;
	kfree(dtsec);

	return 0;
}