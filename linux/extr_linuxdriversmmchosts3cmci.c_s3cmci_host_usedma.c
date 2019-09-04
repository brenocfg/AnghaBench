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
struct s3cmci_host {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool s3cmci_host_usedma(struct s3cmci_host *host)
{
#ifdef CONFIG_MMC_S3C_PIO
	return false;
#else /* CONFIG_MMC_S3C_DMA */
	return true;
#endif
}