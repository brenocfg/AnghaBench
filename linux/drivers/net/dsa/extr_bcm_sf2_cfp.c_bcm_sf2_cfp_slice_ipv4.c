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
struct flow_dissector_key_ports {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct flow_dissector_key_ipv4_addrs {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int CORE_CFP_DATA_PORT (int) ; 
 int CORE_CFP_MASK_PORT (int) ; 
 int SLICE_NUM (unsigned int) ; 
 int SLICE_VALID ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_writel (struct bcm_sf2_priv*,int,int) ; 

__attribute__((used)) static void bcm_sf2_cfp_slice_ipv4(struct bcm_sf2_priv *priv,
				   struct flow_dissector_key_ipv4_addrs *addrs,
				   struct flow_dissector_key_ports *ports,
				   unsigned int slice_num,
				   bool mask)
{
	u32 reg, offset;

	/* C-Tag		[31:24]
	 * UDF_n_A8		[23:8]
	 * UDF_n_A7		[7:0]
	 */
	reg = 0;
	if (mask)
		offset = CORE_CFP_MASK_PORT(4);
	else
		offset = CORE_CFP_DATA_PORT(4);
	core_writel(priv, reg, offset);

	/* UDF_n_A7		[31:24]
	 * UDF_n_A6		[23:8]
	 * UDF_n_A5		[7:0]
	 */
	reg = be16_to_cpu(ports->dst) >> 8;
	if (mask)
		offset = CORE_CFP_MASK_PORT(3);
	else
		offset = CORE_CFP_DATA_PORT(3);
	core_writel(priv, reg, offset);

	/* UDF_n_A5		[31:24]
	 * UDF_n_A4		[23:8]
	 * UDF_n_A3		[7:0]
	 */
	reg = (be16_to_cpu(ports->dst) & 0xff) << 24 |
	      (u32)be16_to_cpu(ports->src) << 8 |
	      (be32_to_cpu(addrs->dst) & 0x0000ff00) >> 8;
	if (mask)
		offset = CORE_CFP_MASK_PORT(2);
	else
		offset = CORE_CFP_DATA_PORT(2);
	core_writel(priv, reg, offset);

	/* UDF_n_A3		[31:24]
	 * UDF_n_A2		[23:8]
	 * UDF_n_A1		[7:0]
	 */
	reg = (u32)(be32_to_cpu(addrs->dst) & 0xff) << 24 |
	      (u32)(be32_to_cpu(addrs->dst) >> 16) << 8 |
	      (be32_to_cpu(addrs->src) & 0x0000ff00) >> 8;
	if (mask)
		offset = CORE_CFP_MASK_PORT(1);
	else
		offset = CORE_CFP_DATA_PORT(1);
	core_writel(priv, reg, offset);

	/* UDF_n_A1		[31:24]
	 * UDF_n_A0		[23:8]
	 * Reserved		[7:4]
	 * Slice ID		[3:2]
	 * Slice valid		[1:0]
	 */
	reg = (u32)(be32_to_cpu(addrs->src) & 0xff) << 24 |
	      (u32)(be32_to_cpu(addrs->src) >> 16) << 8 |
	      SLICE_NUM(slice_num) | SLICE_VALID;
	if (mask)
		offset = CORE_CFP_MASK_PORT(0);
	else
		offset = CORE_CFP_DATA_PORT(0);
	core_writel(priv, reg, offset);
}