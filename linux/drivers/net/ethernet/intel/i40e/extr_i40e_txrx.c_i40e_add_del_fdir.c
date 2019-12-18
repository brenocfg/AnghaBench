#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {TYPE_1__* pdev; } ;
struct i40e_fdir_filter {int flow_type; int ip4_proto; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int FLOW_EXT ; 
#define  IPPROTO_IP 135 
#define  IPPROTO_SCTP 134 
#define  IPPROTO_TCP 133 
#define  IPPROTO_UDP 132 
#define  IP_USER_FLOW 131 
#define  SCTP_V4_FLOW 130 
#define  TCP_V4_FLOW 129 
#define  UDP_V4_FLOW 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int i40e_add_del_fdir_ipv4 (struct i40e_vsi*,struct i40e_fdir_filter*,int) ; 
 int i40e_add_del_fdir_sctpv4 (struct i40e_vsi*,struct i40e_fdir_filter*,int) ; 
 int i40e_add_del_fdir_tcpv4 (struct i40e_vsi*,struct i40e_fdir_filter*,int) ; 
 int i40e_add_del_fdir_udpv4 (struct i40e_vsi*,struct i40e_fdir_filter*,int) ; 

int i40e_add_del_fdir(struct i40e_vsi *vsi,
		      struct i40e_fdir_filter *input, bool add)
{
	struct i40e_pf *pf = vsi->back;
	int ret;

	switch (input->flow_type & ~FLOW_EXT) {
	case TCP_V4_FLOW:
		ret = i40e_add_del_fdir_tcpv4(vsi, input, add);
		break;
	case UDP_V4_FLOW:
		ret = i40e_add_del_fdir_udpv4(vsi, input, add);
		break;
	case SCTP_V4_FLOW:
		ret = i40e_add_del_fdir_sctpv4(vsi, input, add);
		break;
	case IP_USER_FLOW:
		switch (input->ip4_proto) {
		case IPPROTO_TCP:
			ret = i40e_add_del_fdir_tcpv4(vsi, input, add);
			break;
		case IPPROTO_UDP:
			ret = i40e_add_del_fdir_udpv4(vsi, input, add);
			break;
		case IPPROTO_SCTP:
			ret = i40e_add_del_fdir_sctpv4(vsi, input, add);
			break;
		case IPPROTO_IP:
			ret = i40e_add_del_fdir_ipv4(vsi, input, add);
			break;
		default:
			/* We cannot support masking based on protocol */
			dev_info(&pf->pdev->dev, "Unsupported IPv4 protocol 0x%02x\n",
				 input->ip4_proto);
			return -EINVAL;
		}
		break;
	default:
		dev_info(&pf->pdev->dev, "Unsupported flow type 0x%02x\n",
			 input->flow_type);
		return -EINVAL;
	}

	/* The buffer allocated here will be normally be freed by
	 * i40e_clean_fdir_tx_irq() as it reclaims resources after transmit
	 * completion. In the event of an error adding the buffer to the FDIR
	 * ring, it will immediately be freed. It may also be freed by
	 * i40e_clean_tx_ring() when closing the VSI.
	 */
	return ret;
}