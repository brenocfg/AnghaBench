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
struct cxlflash_cfg {scalar_t__ async_reset_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_synchronize_cookie (scalar_t__) ; 

__attribute__((used)) static void cxlflash_reset_sync(struct cxlflash_cfg *cfg)
{
	if (cfg->async_reset_cookie == 0)
		return;

	/* Wait until all async calls prior to this cookie have completed */
	async_synchronize_cookie(cfg->async_reset_cookie + 1);
	cfg->async_reset_cookie = 0;
}