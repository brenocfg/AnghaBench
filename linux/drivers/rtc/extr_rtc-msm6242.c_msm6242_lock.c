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
struct msm6242_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSM6242_CD ; 
 int MSM6242_CD_BUSY ; 
 int /*<<< orphan*/  MSM6242_CD_HOLD ; 
 int /*<<< orphan*/  msm6242_clear (struct msm6242_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msm6242_read (struct msm6242_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm6242_set (struct msm6242_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void msm6242_lock(struct msm6242_priv *priv)
{
	int cnt = 5;

	msm6242_set(priv, MSM6242_CD_HOLD, MSM6242_CD);

	while ((msm6242_read(priv, MSM6242_CD) & MSM6242_CD_BUSY) && cnt) {
		msm6242_clear(priv, MSM6242_CD_HOLD, MSM6242_CD);
		udelay(70);
		msm6242_set(priv, MSM6242_CD_HOLD, MSM6242_CD);
		cnt--;
	}

	if (!cnt)
		pr_warn("timed out waiting for RTC (0x%x)\n",
			msm6242_read(priv, MSM6242_CD));
}