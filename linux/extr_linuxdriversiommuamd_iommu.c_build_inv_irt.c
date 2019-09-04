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
typedef  int /*<<< orphan*/  u16 ;
struct iommu_cmd {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INV_IRT ; 
 int /*<<< orphan*/  CMD_SET_TYPE (struct iommu_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iommu_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void build_inv_irt(struct iommu_cmd *cmd, u16 devid)
{
	memset(cmd, 0, sizeof(*cmd));
	cmd->data[0] = devid;
	CMD_SET_TYPE(cmd, CMD_INV_IRT);
}