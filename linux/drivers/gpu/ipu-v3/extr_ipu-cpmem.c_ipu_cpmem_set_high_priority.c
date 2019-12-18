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
struct ipuv3_channel {int num; struct ipu_soc* ipu; } ;
struct ipu_soc {scalar_t__ ipu_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDMAC_CHA_PRI (int) ; 
 scalar_t__ IPUV3EX ; 
 int /*<<< orphan*/  IPU_FIELD_ID ; 
 int /*<<< orphan*/  ipu_ch_param_write_field (struct ipuv3_channel*,int /*<<< orphan*/ ,int) ; 
 int ipu_idmac_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_write (struct ipu_soc*,int,int /*<<< orphan*/ ) ; 

void ipu_cpmem_set_high_priority(struct ipuv3_channel *ch)
{
	struct ipu_soc *ipu = ch->ipu;
	u32 val;

	if (ipu->ipu_type == IPUV3EX)
		ipu_ch_param_write_field(ch, IPU_FIELD_ID, 1);

	val = ipu_idmac_read(ipu, IDMAC_CHA_PRI(ch->num));
	val |= 1 << (ch->num % 32);
	ipu_idmac_write(ipu, val, IDMAC_CHA_PRI(ch->num));
}