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
typedef  int /*<<< orphan*/  u8 ;
struct i40e_rx_ptype_decoded {scalar_t__ outer_ip; scalar_t__ payload_layer; int /*<<< orphan*/  known; } ;

/* Variables and functions */
 scalar_t__ I40E_RX_PTYPE_OUTER_IP ; 
 scalar_t__ I40E_RX_PTYPE_PAYLOAD_LAYER_PAY3 ; 
 scalar_t__ I40E_RX_PTYPE_PAYLOAD_LAYER_PAY4 ; 
 int PKT_HASH_TYPE_L2 ; 
 int PKT_HASH_TYPE_L3 ; 
 int PKT_HASH_TYPE_L4 ; 
 int PKT_HASH_TYPE_NONE ; 
 struct i40e_rx_ptype_decoded decode_rx_desc_ptype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int i40e_ptype_to_htype(u8 ptype)
{
	struct i40e_rx_ptype_decoded decoded = decode_rx_desc_ptype(ptype);

	if (!decoded.known)
		return PKT_HASH_TYPE_NONE;

	if (decoded.outer_ip == I40E_RX_PTYPE_OUTER_IP &&
	    decoded.payload_layer == I40E_RX_PTYPE_PAYLOAD_LAYER_PAY4)
		return PKT_HASH_TYPE_L4;
	else if (decoded.outer_ip == I40E_RX_PTYPE_OUTER_IP &&
		 decoded.payload_layer == I40E_RX_PTYPE_PAYLOAD_LAYER_PAY3)
		return PKT_HASH_TYPE_L3;
	else
		return PKT_HASH_TYPE_L2;
}