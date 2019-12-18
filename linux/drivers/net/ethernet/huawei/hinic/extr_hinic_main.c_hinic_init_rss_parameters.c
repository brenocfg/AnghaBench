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
struct TYPE_2__ {int tcp_ipv6_ext; int ipv6_ext; int tcp_ipv6; int ipv6; int tcp_ipv4; int ipv4; int udp_ipv6; int udp_ipv4; } ;
struct hinic_dev {TYPE_1__ rss_type; int /*<<< orphan*/  rss_hash_engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_RSS_HASH_ENGINE_TYPE_XOR ; 

__attribute__((used)) static void hinic_init_rss_parameters(struct hinic_dev *nic_dev)
{
	nic_dev->rss_hash_engine = HINIC_RSS_HASH_ENGINE_TYPE_XOR;
	nic_dev->rss_type.tcp_ipv6_ext = 1;
	nic_dev->rss_type.ipv6_ext = 1;
	nic_dev->rss_type.tcp_ipv6 = 1;
	nic_dev->rss_type.ipv6 = 1;
	nic_dev->rss_type.tcp_ipv4 = 1;
	nic_dev->rss_type.ipv4 = 1;
	nic_dev->rss_type.udp_ipv6 = 1;
	nic_dev->rss_type.udp_ipv4 = 1;
}