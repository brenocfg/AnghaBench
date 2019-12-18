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
struct seq_file {struct rsi_common* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  patch_num; int /*<<< orphan*/  release_num; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct rsi_common {TYPE_1__ lmac_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsi_version_read(struct seq_file *seq, void *data)
{
	struct rsi_common *common = seq->private;

	seq_printf(seq, "LMAC   : %d.%d.%d.%d\n",
		   common->lmac_ver.major,
		   common->lmac_ver.minor,
		   common->lmac_ver.release_num,
		   common->lmac_ver.patch_num);

	return 0;
}