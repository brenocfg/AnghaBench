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
typedef  int u8 ;
typedef  int u32 ;
struct ssbi {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SSBI_PA_CMD ; 
 int /*<<< orphan*/  SSBI_PA_RD_STATUS ; 
 int SSBI_PA_RD_STATUS_TRANS_DENIED ; 
 int SSBI_PA_RD_STATUS_TRANS_DONE ; 
 int SSBI_TIMEOUT_US ; 
 int ssbi_readl (struct ssbi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssbi_writel (struct ssbi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline int
ssbi_pa_transfer(struct ssbi *ssbi, u32 cmd, u8 *data)
{
	u32 timeout = SSBI_TIMEOUT_US;
	u32 rd_status = 0;

	ssbi_writel(ssbi, cmd, SSBI_PA_CMD);

	while (timeout--) {
		rd_status = ssbi_readl(ssbi, SSBI_PA_RD_STATUS);

		if (rd_status & SSBI_PA_RD_STATUS_TRANS_DENIED)
			return -EPERM;

		if (rd_status & SSBI_PA_RD_STATUS_TRANS_DONE) {
			if (data)
				*data = rd_status & 0xff;
			return 0;
		}
		udelay(1);
	}

	return -ETIMEDOUT;
}