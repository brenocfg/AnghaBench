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
struct sclp_core_info {int configured; int standby; int combined; int /*<<< orphan*/  core; } ;
struct sclp_core_entry {int dummy; } ;
struct read_cpu_info_sccb {int nr_configured; int nr_standby; int offset_configured; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (struct sclp_core_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void sclp_fill_core_info(struct sclp_core_info *info,
				       struct read_cpu_info_sccb *sccb)
{
	char *page = (char *) sccb;

	memset(info, 0, sizeof(*info));
	info->configured = sccb->nr_configured;
	info->standby = sccb->nr_standby;
	info->combined = sccb->nr_configured + sccb->nr_standby;
	memcpy(&info->core, page + sccb->offset_configured,
	       info->combined * sizeof(struct sclp_core_entry));
}