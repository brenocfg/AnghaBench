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
typedef  int u32 ;
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int CTXMEMSIZE ; 
 int /*<<< orphan*/  LmMnINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int asd_read_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 asd_get_cmdctx_size(struct asd_ha_struct *asd_ha)
{
	/* DCHREVISION returns 0, possibly broken */
	u32 ctxmemsize = asd_read_reg_dword(asd_ha, LmMnINT(0,0)) & CTXMEMSIZE;
	return ctxmemsize ? 65536 : 32768;
}