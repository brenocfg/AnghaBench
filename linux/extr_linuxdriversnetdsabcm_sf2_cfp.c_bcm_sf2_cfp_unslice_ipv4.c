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
typedef  int u16 ;
struct ethtool_tcpip4_spec {void* ip4src; void* ip4dst; void* psrc; void* pdst; } ;
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int CORE_CFP_DATA_PORT (int) ; 
 int CORE_CFP_MASK_PORT (int) ; 
 int EINVAL ; 
 int SLICE_VALID ; 
 int core_readl (struct bcm_sf2_priv*,int) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static int bcm_sf2_cfp_unslice_ipv4(struct bcm_sf2_priv *priv,
				    struct ethtool_tcpip4_spec *v4_spec,
				    bool mask)
{
	u32 reg, offset, ipv4;
	u16 src_dst_port;

	if (mask)
		offset = CORE_CFP_MASK_PORT(3);
	else
		offset = CORE_CFP_DATA_PORT(3);

	reg = core_readl(priv, offset);
	/* src port [15:8] */
	src_dst_port = reg << 8;

	if (mask)
		offset = CORE_CFP_MASK_PORT(2);
	else
		offset = CORE_CFP_DATA_PORT(2);

	reg = core_readl(priv, offset);
	/* src port [7:0] */
	src_dst_port |= (reg >> 24);

	v4_spec->pdst = cpu_to_be16(src_dst_port);
	v4_spec->psrc = cpu_to_be16((u16)(reg >> 8));

	/* IPv4 dst [15:8] */
	ipv4 = (reg & 0xff) << 8;

	if (mask)
		offset = CORE_CFP_MASK_PORT(1);
	else
		offset = CORE_CFP_DATA_PORT(1);

	reg = core_readl(priv, offset);
	/* IPv4 dst [31:16] */
	ipv4 |= ((reg >> 8) & 0xffff) << 16;
	/* IPv4 dst [7:0] */
	ipv4 |= (reg >> 24) & 0xff;
	v4_spec->ip4dst = cpu_to_be32(ipv4);

	/* IPv4 src [15:8] */
	ipv4 = (reg & 0xff) << 8;

	if (mask)
		offset = CORE_CFP_MASK_PORT(0);
	else
		offset = CORE_CFP_DATA_PORT(0);
	reg = core_readl(priv, offset);

	/* Once the TCAM is programmed, the mask reflects the slice number
	 * being matched, don't bother checking it when reading back the
	 * mask spec
	 */
	if (!mask && !(reg & SLICE_VALID))
		return -EINVAL;

	/* IPv4 src [7:0] */
	ipv4 |= (reg >> 24) & 0xff;
	/* IPv4 src [31:16] */
	ipv4 |= ((reg >> 8) & 0xffff) << 16;
	v4_spec->ip4src = cpu_to_be32(ipv4);

	return 0;
}