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
struct bcm_sf2_priv {int dummy; } ;
typedef  int __be32 ;
typedef  int __be16 ;

/* Variables and functions */
 int CORE_CFP_DATA_PORT (int) ; 
 int CORE_CFP_MASK_PORT (int) ; 
 int EINVAL ; 
 int SLICE_VALID ; 
 int core_readl (struct bcm_sf2_priv*,int) ; 
 int cpu_to_be32 (int) ; 

__attribute__((used)) static int bcm_sf2_cfp_unslice_ipv6(struct bcm_sf2_priv *priv,
				     __be32 *ip6_addr, __be16 *port,
				     bool mask)
{
	u32 reg, tmp, offset;

	/* C-Tag		[31:24]
	 * UDF_n_B8		[23:8] (port)
	 * UDF_n_B7 (upper)	[7:0] (addr[15:8])
	 */
	if (mask)
		offset = CORE_CFP_MASK_PORT(4);
	else
		offset = CORE_CFP_DATA_PORT(4);
	reg = core_readl(priv, offset);
	*port = cpu_to_be32(reg) >> 8;
	tmp = (u32)(reg & 0xff) << 8;

	/* UDF_n_B7 (lower)	[31:24] (addr[7:0])
	 * UDF_n_B6		[23:8] (addr[31:16])
	 * UDF_n_B5 (upper)	[7:0] (addr[47:40])
	 */
	if (mask)
		offset = CORE_CFP_MASK_PORT(3);
	else
		offset = CORE_CFP_DATA_PORT(3);
	reg = core_readl(priv, offset);
	tmp |= (reg >> 24) & 0xff;
	tmp |= (u32)((reg >> 8) << 16);
	ip6_addr[3] = cpu_to_be32(tmp);
	tmp = (u32)(reg & 0xff) << 8;

	/* UDF_n_B5 (lower)	[31:24] (addr[39:32])
	 * UDF_n_B4		[23:8] (addr[63:48])
	 * UDF_n_B3 (upper)	[7:0] (addr[79:72])
	 */
	if (mask)
		offset = CORE_CFP_MASK_PORT(2);
	else
		offset = CORE_CFP_DATA_PORT(2);
	reg = core_readl(priv, offset);
	tmp |= (reg >> 24) & 0xff;
	tmp |= (u32)((reg >> 8) << 16);
	ip6_addr[2] = cpu_to_be32(tmp);
	tmp = (u32)(reg & 0xff) << 8;

	/* UDF_n_B3 (lower)	[31:24] (addr[71:64])
	 * UDF_n_B2		[23:8] (addr[95:80])
	 * UDF_n_B1 (upper)	[7:0] (addr[111:104])
	 */
	if (mask)
		offset = CORE_CFP_MASK_PORT(1);
	else
		offset = CORE_CFP_DATA_PORT(1);
	reg = core_readl(priv, offset);
	tmp |= (reg >> 24) & 0xff;
	tmp |= (u32)((reg >> 8) << 16);
	ip6_addr[1] = cpu_to_be32(tmp);
	tmp = (u32)(reg & 0xff) << 8;

	/* UDF_n_B1 (lower)	[31:24] (addr[103:96])
	 * UDF_n_B0		[23:8] (addr[127:112])
	 * Reserved		[7:4]
	 * Slice ID		[3:2]
	 * Slice valid		[1:0]
	 */
	if (mask)
		offset = CORE_CFP_MASK_PORT(0);
	else
		offset = CORE_CFP_DATA_PORT(0);
	reg = core_readl(priv, offset);
	tmp |= (reg >> 24) & 0xff;
	tmp |= (u32)((reg >> 8) << 16);
	ip6_addr[0] = cpu_to_be32(tmp);

	if (!mask && !(reg & SLICE_VALID))
		return -EINVAL;

	return 0;
}