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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int ale_entries; } ;
struct cpsw_common {TYPE_1__ data; } ;

/* Variables and functions */
 int ALE_ENTRY_WORDS ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 

int cpsw_get_regs_len(struct net_device *ndev)
{
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	return cpsw->data.ale_entries * ALE_ENTRY_WORDS * sizeof(u32);
}