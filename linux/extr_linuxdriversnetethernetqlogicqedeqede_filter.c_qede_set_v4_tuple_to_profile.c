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
struct qede_dev {int dummy; } ;
struct qede_arfs_tuple {int /*<<< orphan*/  stringify; int /*<<< orphan*/  build_hdr; int /*<<< orphan*/  ip_comp; int /*<<< orphan*/  mode; scalar_t__ src_ipv4; scalar_t__ dst_ipv4; scalar_t__ dst_port; scalar_t__ src_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  QED_FILTER_CONFIG_MODE_5_TUPLE ; 
 int /*<<< orphan*/  QED_FILTER_CONFIG_MODE_IP_DEST ; 
 int /*<<< orphan*/  QED_FILTER_CONFIG_MODE_IP_SRC ; 
 int /*<<< orphan*/  QED_FILTER_CONFIG_MODE_L4_PORT ; 
 int /*<<< orphan*/  qede_flow_build_ipv4_hdr ; 
 int /*<<< orphan*/  qede_flow_spec_ipv4_cmp ; 
 int /*<<< orphan*/  qede_flow_stringify_ipv4_hdr ; 

__attribute__((used)) static int qede_set_v4_tuple_to_profile(struct qede_dev *edev,
					struct qede_arfs_tuple *t)
{
	/* We must have Only 4-tuples/l4 port/src ip/dst ip
	 * as an input.
	 */
	if (t->src_port && t->dst_port && t->src_ipv4 && t->dst_ipv4) {
		t->mode = QED_FILTER_CONFIG_MODE_5_TUPLE;
	} else if (!t->src_port && t->dst_port &&
		   !t->src_ipv4 && !t->dst_ipv4) {
		t->mode = QED_FILTER_CONFIG_MODE_L4_PORT;
	} else if (!t->src_port && !t->dst_port &&
		   !t->dst_ipv4 && t->src_ipv4) {
		t->mode = QED_FILTER_CONFIG_MODE_IP_SRC;
	} else if (!t->src_port && !t->dst_port &&
		   t->dst_ipv4 && !t->src_ipv4) {
		t->mode = QED_FILTER_CONFIG_MODE_IP_DEST;
	} else {
		DP_INFO(edev, "Invalid N-tuple\n");
		return -EOPNOTSUPP;
	}

	t->ip_comp = qede_flow_spec_ipv4_cmp;
	t->build_hdr = qede_flow_build_ipv4_hdr;
	t->stringify = qede_flow_stringify_ipv4_hdr;

	return 0;
}