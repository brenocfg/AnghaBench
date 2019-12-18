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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  lock; } ;
struct iwl_priv {TYPE_1__ statistics; } ;

/* Variables and functions */
 int UCODE_STATISTICS_CLEAR_MSK ; 
 int UCODE_STATISTICS_FREQUENCY_MSK ; 
 int UCODE_STATISTICS_NARROW_BAND_MSK ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ scnprintf (char*,int,char*,...) ; 

__attribute__((used)) static int iwl_statistics_flag(struct iwl_priv *priv, char *buf, int bufsz)
{
	int p = 0;
	u32 flag;

	lockdep_assert_held(&priv->statistics.lock);

	flag = le32_to_cpu(priv->statistics.flag);

	p += scnprintf(buf + p, bufsz - p, "Statistics Flag(0x%X):\n", flag);
	if (flag & UCODE_STATISTICS_CLEAR_MSK)
		p += scnprintf(buf + p, bufsz - p,
		"\tStatistics have been cleared\n");
	p += scnprintf(buf + p, bufsz - p, "\tOperational Frequency: %s\n",
		(flag & UCODE_STATISTICS_FREQUENCY_MSK)
		? "2.4 GHz" : "5.2 GHz");
	p += scnprintf(buf + p, bufsz - p, "\tTGj Narrow Band: %s\n",
		(flag & UCODE_STATISTICS_NARROW_BAND_MSK)
		 ? "enabled" : "disabled");

	return p;
}