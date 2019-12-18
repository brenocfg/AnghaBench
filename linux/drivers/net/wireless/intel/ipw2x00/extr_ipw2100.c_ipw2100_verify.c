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
struct ipw2100_priv {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EIO ; 
 int IPW_DATA_DOA_DEBUG_VALUE ; 
 int IPW_REG_DOA_DEBUG_AREA_END ; 
 int IPW_REG_DOA_DEBUG_AREA_START ; 
 int IPW_REG_DOMAIN_1_OFFSET ; 
 int /*<<< orphan*/  read_register (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  write_register (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ipw2100_verify(struct ipw2100_priv *priv)
{
	u32 data1, data2;
	u32 address;

	u32 val1 = 0x76543210;
	u32 val2 = 0xFEDCBA98;

	/* Domain 0 check - all values should be DOA_DEBUG */
	for (address = IPW_REG_DOA_DEBUG_AREA_START;
	     address < IPW_REG_DOA_DEBUG_AREA_END; address += sizeof(u32)) {
		read_register(priv->net_dev, address, &data1);
		if (data1 != IPW_DATA_DOA_DEBUG_VALUE)
			return -EIO;
	}

	/* Domain 1 check - use arbitrary read/write compare  */
	for (address = 0; address < 5; address++) {
		/* The memory area is not used now */
		write_register(priv->net_dev, IPW_REG_DOMAIN_1_OFFSET + 0x32,
			       val1);
		write_register(priv->net_dev, IPW_REG_DOMAIN_1_OFFSET + 0x36,
			       val2);
		read_register(priv->net_dev, IPW_REG_DOMAIN_1_OFFSET + 0x32,
			      &data1);
		read_register(priv->net_dev, IPW_REG_DOMAIN_1_OFFSET + 0x36,
			      &data2);
		if (val1 == data1 && val2 == data2)
			return 0;
	}

	return -EIO;
}