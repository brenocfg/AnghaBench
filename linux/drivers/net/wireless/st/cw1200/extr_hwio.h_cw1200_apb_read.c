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
typedef  int /*<<< orphan*/  u32 ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST90TDS_CONFIG_PRFETCH_BIT ; 
 int /*<<< orphan*/  ST90TDS_SRAM_DPORT_REG_ID ; 
 int cw1200_indirect_read (struct cw1200_common*,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cw1200_apb_read(struct cw1200_common *priv, u32 addr,
				  void *buf, size_t buf_len)
{
	return cw1200_indirect_read(priv, addr, buf, buf_len,
				    ST90TDS_CONFIG_PRFETCH_BIT,
				    ST90TDS_SRAM_DPORT_REG_ID);
}