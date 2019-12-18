#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ctlr_info {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void warn_zero_length_transfer(struct ctlr_info *h,
						u8 *cdb, int cdb_len,
						const char *func)
{
	dev_warn(&h->pdev->dev,
		 "%s: Blocking zero-length request: CDB:%*phN\n",
		 func, cdb_len, cdb);
}