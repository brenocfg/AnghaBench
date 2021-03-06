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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
typedef  enum desc_id { ____Placeholder_desc_id } desc_id ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_DESC_OFS_CMDSTS ; 
 int /*<<< orphan*/  ave_desc_read (struct net_device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ave_desc_read_cmdsts(struct net_device *ndev, enum desc_id id,
				int entry)
{
	return ave_desc_read(ndev, id, entry, AVE_DESC_OFS_CMDSTS);
}