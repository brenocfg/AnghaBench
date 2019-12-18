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
typedef  int /*<<< orphan*/  ulong ;
struct cxlflash_cfg {struct afu* afu; } ;
struct afu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 

__attribute__((used)) static void free_mem(struct cxlflash_cfg *cfg)
{
	struct afu *afu = cfg->afu;

	if (cfg->afu) {
		free_pages((ulong)afu, get_order(sizeof(struct afu)));
		cfg->afu = NULL;
	}
}