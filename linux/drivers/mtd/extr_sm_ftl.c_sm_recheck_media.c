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
struct sm_ftl {int unstable; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  sm_printk (char*) ; 
 scalar_t__ sm_read_cis (struct sm_ftl*) ; 

__attribute__((used)) static int sm_recheck_media(struct sm_ftl *ftl)
{
	if (sm_read_cis(ftl)) {

		if (!ftl->unstable) {
			sm_printk("media unstable, not allowing writes");
			ftl->unstable = 1;
		}
		return -EIO;
	}
	return 0;
}