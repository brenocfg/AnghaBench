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
 int /*<<< orphan*/  CAPP_WDR_EN ; 
 int /*<<< orphan*/  MON_TONE_CTL ; 
 int /*<<< orphan*/  REG_CAPTURE ; 
 int m5mols_set_mode (struct m5mols_info*,int /*<<< orphan*/ ) ; 
 int m5mols_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int m5mols_set_wdr(struct m5mols_info *info, int wdr)
{
	int ret;

	ret = m5mols_write(&info->sd, MON_TONE_CTL, wdr ? 9 : 5);
	if (ret < 0)
		return ret;

	ret = m5mols_set_mode(info, REG_CAPTURE);
	if (ret < 0)
		return ret;

	return m5mols_write(&info->sd, CAPP_WDR_EN, wdr);
}