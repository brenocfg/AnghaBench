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
struct fman_mac {struct fman_mac* cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_init_resources (struct fman_mac*) ; 
 int /*<<< orphan*/  kfree (struct fman_mac*) ; 

int tgec_free(struct fman_mac *tgec)
{
	free_init_resources(tgec);

	kfree(tgec->cfg);
	kfree(tgec);

	return 0;
}