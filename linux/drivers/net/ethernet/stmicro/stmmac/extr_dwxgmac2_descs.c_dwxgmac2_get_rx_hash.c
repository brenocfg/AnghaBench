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
struct dma_desc {int /*<<< orphan*/  des1; int /*<<< orphan*/  des3; } ;
typedef  enum pkt_hash_types { ____Placeholder_pkt_hash_types } pkt_hash_types ;

/* Variables and functions */
 int EINVAL ; 
 int PKT_HASH_TYPE_L3 ; 
 int PKT_HASH_TYPE_L4 ; 
#define  XGMAC_L34T_IP4TCP 131 
#define  XGMAC_L34T_IP4UDP 130 
#define  XGMAC_L34T_IP6TCP 129 
#define  XGMAC_L34T_IP6UDP 128 
 unsigned int XGMAC_RDES3_L34T ; 
 unsigned int XGMAC_RDES3_L34T_SHIFT ; 
 unsigned int XGMAC_RDES3_RSV ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwxgmac2_get_rx_hash(struct dma_desc *p, u32 *hash,
				enum pkt_hash_types *type)
{
	unsigned int rdes3 = le32_to_cpu(p->des3);
	u32 ptype;

	if (rdes3 & XGMAC_RDES3_RSV) {
		ptype = (rdes3 & XGMAC_RDES3_L34T) >> XGMAC_RDES3_L34T_SHIFT;

		switch (ptype) {
		case XGMAC_L34T_IP4TCP:
		case XGMAC_L34T_IP4UDP:
		case XGMAC_L34T_IP6TCP:
		case XGMAC_L34T_IP6UDP:
			*type = PKT_HASH_TYPE_L4;
			break;
		default:
			*type = PKT_HASH_TYPE_L3;
			break;
		}

		*hash = le32_to_cpu(p->des1);
		return 0;
	}

	return -EINVAL;
}