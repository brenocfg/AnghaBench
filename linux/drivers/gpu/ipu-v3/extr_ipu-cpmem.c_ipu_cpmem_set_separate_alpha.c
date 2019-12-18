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
struct ipuv3_channel {int /*<<< orphan*/  num; struct ipu_soc* ipu; } ;
struct ipu_soc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDMAC_SEP_ALPHA ; 
 int /*<<< orphan*/  IPU_FIELD_ALBM ; 
 int /*<<< orphan*/  IPU_FIELD_ALU ; 
 int /*<<< orphan*/  IPU_FIELD_CRE ; 
 int /*<<< orphan*/  ipu_ch_param_write_field (struct ipuv3_channel*,int /*<<< orphan*/ ,int) ; 
 int ipu_channel_albm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_write (struct ipu_soc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipu_cpmem_set_separate_alpha(struct ipuv3_channel *ch)
{
	struct ipu_soc *ipu = ch->ipu;
	int albm;
	u32 val;

	albm = ipu_channel_albm(ch->num);
	if (albm < 0)
		return;

	ipu_ch_param_write_field(ch, IPU_FIELD_ALU, 1);
	ipu_ch_param_write_field(ch, IPU_FIELD_ALBM, albm);
	ipu_ch_param_write_field(ch, IPU_FIELD_CRE, 1);

	val = ipu_idmac_read(ipu, IDMAC_SEP_ALPHA);
	val |= BIT(ch->num);
	ipu_idmac_write(ipu, val, IDMAC_SEP_ALPHA);
}