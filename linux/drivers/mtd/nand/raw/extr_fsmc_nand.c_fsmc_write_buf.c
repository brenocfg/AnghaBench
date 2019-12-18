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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct fsmc_nand_data {int /*<<< orphan*/  data_va; } ;

/* Variables and functions */
 scalar_t__ IS_ALIGNED (int,int) ; 
 int /*<<< orphan*/  writeb_relaxed (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsmc_write_buf(struct fsmc_nand_data *host, const u8 *buf,
			   int len)
{
	int i;

	if (IS_ALIGNED((uintptr_t)buf, sizeof(u32)) &&
	    IS_ALIGNED(len, sizeof(u32))) {
		u32 *p = (u32 *)buf;

		len = len >> 2;
		for (i = 0; i < len; i++)
			writel_relaxed(p[i], host->data_va);
	} else {
		for (i = 0; i < len; i++)
			writeb_relaxed(buf[i], host->data_va);
	}
}