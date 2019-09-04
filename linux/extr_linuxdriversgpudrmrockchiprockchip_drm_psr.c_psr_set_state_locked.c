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
struct psr_drv {scalar_t__ inhibit_count; int enabled; int (* set ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  encoder; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int psr_set_state_locked(struct psr_drv *psr, bool enable)
{
	int ret;

	if (psr->inhibit_count > 0)
		return -EINVAL;

	if (enable == psr->enabled)
		return 0;

	ret = psr->set(psr->encoder, enable);
	if (ret)
		return ret;

	psr->enabled = enable;
	return 0;
}