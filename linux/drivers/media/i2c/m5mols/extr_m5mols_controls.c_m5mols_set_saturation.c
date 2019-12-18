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
struct m5mols_info {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MON_CHROMA_EN ; 
 int /*<<< orphan*/  MON_CHROMA_LVL ; 
 int REG_CHROMA_ON ; 
 int m5mols_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int m5mols_set_saturation(struct m5mols_info *info, int val)
{
	int ret = m5mols_write(&info->sd, MON_CHROMA_LVL, val);
	if (ret < 0)
		return ret;

	return m5mols_write(&info->sd, MON_CHROMA_EN, REG_CHROMA_ON);
}