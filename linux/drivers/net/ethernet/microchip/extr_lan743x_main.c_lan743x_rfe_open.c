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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFE_RSS_CFG ; 
 int RFE_RSS_CFG_IPV4_ ; 
 int RFE_RSS_CFG_IPV6_ ; 
 int RFE_RSS_CFG_IPV6_EX_ ; 
 int RFE_RSS_CFG_RSS_ENABLE_ ; 
 int RFE_RSS_CFG_RSS_HASH_STORE_ ; 
 int RFE_RSS_CFG_RSS_QUEUE_ENABLE_ ; 
 int RFE_RSS_CFG_TCP_IPV4_ ; 
 int RFE_RSS_CFG_TCP_IPV6_ ; 
 int RFE_RSS_CFG_TCP_IPV6_EX_ ; 
 int RFE_RSS_CFG_UDP_IPV4_ ; 
 int RFE_RSS_CFG_UDP_IPV6_ ; 
 int RFE_RSS_CFG_UDP_IPV6_EX_ ; 
 int RFE_RSS_CFG_VALID_HASH_BITS_ ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lan743x_rfe_open(struct lan743x_adapter *adapter)
{
	lan743x_csr_write(adapter, RFE_RSS_CFG,
		RFE_RSS_CFG_UDP_IPV6_EX_ |
		RFE_RSS_CFG_TCP_IPV6_EX_ |
		RFE_RSS_CFG_IPV6_EX_ |
		RFE_RSS_CFG_UDP_IPV6_ |
		RFE_RSS_CFG_TCP_IPV6_ |
		RFE_RSS_CFG_IPV6_ |
		RFE_RSS_CFG_UDP_IPV4_ |
		RFE_RSS_CFG_TCP_IPV4_ |
		RFE_RSS_CFG_IPV4_ |
		RFE_RSS_CFG_VALID_HASH_BITS_ |
		RFE_RSS_CFG_RSS_QUEUE_ENABLE_ |
		RFE_RSS_CFG_RSS_HASH_STORE_ |
		RFE_RSS_CFG_RSS_ENABLE_);
}